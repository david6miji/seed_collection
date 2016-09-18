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

#include <linux/gpio.h>
#include "base_gpio.h"

#define		THIS_DRV_VER		"0.0.1"
#define		THIS_DRV_NAME		DRIVER_NAME_BASE_GPIO
#define		THIS_DRV_MAJOR		DRIVER_MAJOR_BASE_GPIO

/* global var -----------------------------------------------------------------*/


/* local var ------------------------------------------------------------------*/
// [GPIO 인덱스] = ( [GPIO 구룹 번호] - 1 )*32 + [GPIO 번호]
#define GP2_4_INDEX  36 // (2-1)*32+4
#define GP2_5_INDEX  37 // (2-1)*32+5

static int gpio_forward  = GP2_4_INDEX;
static int gpio_backward = GP2_5_INDEX;

//-----------------------------------------------------------------------------
/** @brief   driver init
	@remark  
*///---------------------------------------------------------------------------
static int __init gb_init(void)
{
	
	int ret;
	
	ret = gpio_request( gpio_forward, "gpio_forward" );
 	if( 0 == ret ){
		gpio_direction_output(gpio_forward, 0);
 	} else {
		printk( "gpio error [index:%d] ret = %d\n", gpio_forward, ret );
	}
	
	ret = gpio_request( gpio_backward, "gpio_backward" );
 	if( 0 == ret ){
		gpio_direction_output(gpio_backward, 0);
 	} else {
		printk( "gpio error [index:%d] ret = %d\n", gpio_forward, ret );
	}
	
	// gpio_set_value(gpio_backward, 1);
	// ret = gpio_get_value(gpio_lcd_get);
	
	return 0;
}
//-----------------------------------------------------------------------------
/** @brief   driver exit
	@remark  
*///----------------------------------------------------------------------------
static void __exit gb_exit(void)
{
	gpio_direction_input(gpio_forward);
	gpio_direction_input(gpio_backward);
	gpio_free(gpio_forward);
	gpio_free(gpio_backward);
}

/*-----------------------------------------------------------------------------*/

module_init(gb_init);
module_exit(gb_exit);

MODULE_AUTHOR("frog@falinux.com");
MODULE_LICENSE("GPL");

/* end */
