/*-----------------------------------------------------------------------------
  file : gpio_main.c
  desc : 
  auth : frog@falinux.com
  date : 2016-07 ~
  noty : linux 3.14 for imx6

-------------------------------------------------------------------------------*/
#ifndef __KERNEL__
#define __KERNEL__
#endif

#ifndef MODULE
#define MODULE
#endif

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h> 
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/slab.h>    
#include <linux/poll.h>     
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/workqueue.h>
#include <linux/irq.h>		
#include <linux/time.h>			
#include <linux/timer.h>		
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <asm/uaccess.h>
#include <asm/ioctl.h>
#include <asm/unistd.h>
#include <asm/io.h>
#include <asm/irq.h>

#include "base_sysfs.h"

static DEFINE_MUTEX(sysfs_lock);
static LIST_HEAD(frogs);

static struct class 	frog_class;

static ssize_t frog_value_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	char 			*start = buf;
	struct frog		*frog;
	
	mutex_lock(&sysfs_lock);
	
	frog = dev_get_drvdata(dev);
	
	buf += sprintf(buf, "%s\n", frog->value );
	
	mutex_unlock(&sysfs_lock);
	
    return buf - start;
}

static ssize_t frog_value_store(struct device *dev,
                 struct device_attribute *attr, const char *buf, size_t size)
{
	ssize_t 		status=0;
	struct frog		*frog;
	char			value[sizeof(frog->value)];
	
	mutex_lock(&sysfs_lock);

	if( sscanf( buf, "%s", value) != 1 ){
		status = -EINVAL;
		goto end_unlock;
	}
	
	frog = dev_get_drvdata(dev);

	strncpy( frog->value, ( const char *) value, sizeof(value) ); 
	
//  status = kstrtoul(buf, 0, &val);
//  if(status){
//		status = -EINVAL;
//		goto end_unlock;
//	}

end_unlock:
	
	mutex_unlock(&sysfs_lock);
	return status ? : size;
}

static const DEVICE_ATTR(value, 0644, frog_value_show, frog_value_store);				
				
static const struct attribute *frog_attrs[] = {
        &dev_attr_value.attr,
        NULL,
};

static const struct attribute_group frog_attr_group = {
        .attrs = (struct attribute **) frog_attrs,
};

static ssize_t export_store( struct class *class,
                             struct class_attribute *attr,
                             const char *buf, size_t size )
{
	char 			**argv;
	int				argc;
	ssize_t 		status=0;
	struct frog		*frog;
	struct device   *dev;
	
	char			name[sizeof(frog->name)];

	mutex_lock(&sysfs_lock);
	
	argv = argv_split(GFP_KERNEL, buf, &argc);
	if(!argv) {
		status = -ENOMEM;
		goto end_unlock;
	}	

	if(!argc) {
		argv_free(argv);
		status = -EINVAL;
		goto end_unlock;
	}	
	
	strncpy( name, ( const char *) argv[0], sizeof(name) ); 
	argv_free(argv);
	
	list_for_each_entry(frog, &frogs, list) {
		if( !strncmp( frog->name, name, sizeof(name) ) ){
			status = -EINVAL;
			goto end_unlock;
		}
	}
	
	frog = kzalloc(sizeof(struct frog), GFP_KERNEL);
	if(IS_ERR(frog)) {
		status = PTR_ERR(frog);
		goto end_unlock;
	}
	
	strncpy( frog->name, ( const char *) name, sizeof(name) ); 
	
	dev = device_create( 	
					&frog_class, 	// struct class *cls	
					NULL, 			// struct device *parent
					MKDEV(0, 0), 	// dev_t devt
					frog, 			// void *drvdata
					frog->name		// const char *fmt, ...
				 );
	if (IS_ERR(dev)) {
		kfree( frog );
		status = PTR_ERR(dev);
		goto end_unlock;
	}
	
	frog->dev = dev;

	status = sysfs_create_group(&dev->kobj, &frog_attr_group);
    if (status){
		kfree( frog );
        goto fail_unregister_device;
	}
	
	list_add_tail(&frog->list, &frogs);
	 
	goto end_unlock;

fail_unregister_device:
	device_unregister(dev);

end_unlock:
	mutex_unlock(&sysfs_lock);
	return status ? : size;
}
	
static ssize_t unexport_store(  struct class *class,
                                struct class_attribute *attr,
                                const char *buf, size_t size)
{
	char 			**argv;
	int				argc;
	ssize_t 		status=0;
	struct frog		*frog;
	struct device   *dev;
	
	char			name[sizeof(frog->name)];
	
	mutex_lock(&sysfs_lock);

	argv = argv_split(GFP_KERNEL, buf, &argc);
	if(!argv) {
		status = -ENOMEM;
		goto end_unlock;
	}	

	if(!argc) {
		argv_free(argv);
		status = -EINVAL;
		goto end_unlock;
	}	

	strncpy( name, ( const char *) argv[0], sizeof(name) ); 
	argv_free(argv);
	
	list_for_each_entry(frog, &frogs, list) {
		if( !strncmp( frog->name, name, sizeof(name) ) ){
			
			dev = frog->dev;
			device_unregister(dev);
			list_del( &frog->list );
			kfree( frog );
			goto end_unlock;
		}
	}
	
	status = -ENODEV;
	
end_unlock:

	mutex_unlock(&sysfs_lock);
	return status ? : size;
}

static ssize_t list_show( struct class *class,
                          struct class_attribute *attr,
                          char *buf )
{
	struct frog		*frog;
	char 			*start = buf;

	mutex_lock(&sysfs_lock);

	list_for_each_entry(frog, &frogs, list) {
		buf += sprintf( buf, "%s\n", frog->name );
	}
	
	mutex_unlock(&sysfs_lock);
    return buf - start;
}

static struct class_attribute frog_class_attrs[] = {
        __ATTR(export,   0200, NULL, export_store),
        __ATTR(unexport, 0200, NULL, unexport_store),
        __ATTR(list, 	 0400, list_show, NULL),
        __ATTR_NULL,
};

static struct class frog_class = {
        .name = "frog",
        .owner = THIS_MODULE,
		.class_attrs =  frog_class_attrs,
};

//-----------------------------------------------------------------------------
/** @brief   driver init
	@remark  
*///---------------------------------------------------------------------------
static int __init sf_init(void)
{
	class_register(&frog_class);

	return 0;
}
//-----------------------------------------------------------------------------
/** @brief   driver exit
	@remark  
*///----------------------------------------------------------------------------
static void __exit sf_exit(void)
{
	struct frog		*frog;
	struct frog		*temp;
	struct device   *dev;
	 
	list_for_each_entry_safe(frog, temp, &frogs, list) {
		
		list_del( &frog->list );
		
		dev = frog->dev;
		device_unregister(dev);
		
		kfree( frog );
	}
	
	class_unregister(&frog_class);
}

/*-----------------------------------------------------------------------------*/

module_init(sf_init);
module_exit(sf_exit);

MODULE_AUTHOR("frog@falinux.com");
MODULE_LICENSE("GPL");

/* end */
