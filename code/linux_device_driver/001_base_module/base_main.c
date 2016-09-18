/*-----------------------------------------------------------------------------
  file : base_main.c
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

#include "base.h"

#define		THIS_DRV_VER		"0.0.1"
#define		THIS_DRV_NAME		DRIVER_NAME_BASE
#define		THIS_DRV_MAJOR		DRIVER_MAJOR_BASE

/* global var -----------------------------------------------------------------*/


/* local var ------------------------------------------------------------------*/

//------------------------------------------------------------------------------
/** @brief   driver init
	@remark  
*///----------------------------------------------------------------------------
static int __init base_init(void)
{
	
	return 0;
}
//------------------------------------------------------------------------------
/** @brief   driver exit
	@remark  
*///----------------------------------------------------------------------------
static void __exit base_exit(void)
{
}

/*-----------------------------------------------------------------------------*/

module_init(base_init);
module_exit(base_exit);

MODULE_AUTHOR("frog@falinux.com");
MODULE_LICENSE("GPL");

/* end */
