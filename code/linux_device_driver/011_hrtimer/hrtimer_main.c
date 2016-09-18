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
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/time.h>			
#include <linux/timer.h>		
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <asm/uaccess.h>
#include <asm/ioctl.h>
#include <asm/unistd.h>
#include <asm/io.h>
#include <asm/irq.h>


#include "base_hrtimer.h"

#define  THIS_DRV_VER		"0.0.1"
#define  THIS_DRV_NAME		DRIVER_NAME_HRTIMER
#define  THIS_DRV_MAJOR		DRIVER_MAJOR_HRTIMER

/* global var -----------------------------------------------------------------*/


/* local var ------------------------------------------------------------------*/

#define MS_TO_NS(x) (x * 1E6L)

static struct hrtimer 	hr_timer;
static        ktime_t 	hr_timer_expiry_time;

static u32    count = 0;

void hrt_hrtimer_start( void )
{
	hrtimer_start( 	
					&hr_timer, 				// hrtimer 주소 
					hr_timer_expiry_time, 	// 함수 호출 시점
					HRTIMER_MODE_REL 		// 함수 호출 시점 기준
				 );
}

enum hrtimer_restart hrt_hrtimer_callback( struct hrtimer *timer )
{

	count++; 
	if( count%1000 == 0 ) {
		printk( "hrt_hrtimer_callback called (%ld).\n", jiffies );
	}
	hrt_hrtimer_start();
	
    return HRTIMER_NORESTART;
}

void hrt_hrtimer_init( const s32 secs, const u32 nsecs )
{
	
	hr_timer_expiry_time = ktime_set( secs, nsecs );
	
	hrtimer_init( 
		&hr_timer, 			// hrtimer 주소 
		CLOCK_MONOTONIC, 	// 대상 시간 
		HRTIMER_MODE_REL    // 처리 시간 기준 모드 		
	);
 
	hr_timer.function = &hrt_hrtimer_callback;
	
}

//-----------------------------------------------------------------------------
/** @brief   driver init
	@remark  
*///----------------------------------------------------------------------------
static int __init hrt_init(void)
{
	
	printk( "HELLO HR TIMER Test\n" );
	
	hrt_hrtimer_init( 0L, MS_TO_NS(1L) );
	
	printk( "Starting hrtimer\n");
	hrt_hrtimer_start();

	return 0;
}
//-----------------------------------------------------------------------------
/** @brief   driver exit
	@remark  
*///----------------------------------------------------------------------------
static void __exit hrt_exit(void)
{
	int ret;

	ret = hrtimer_cancel( &hr_timer );
	if (ret) printk("The timer was still in use...\n");
	
}

/*-----------------------------------------------------------------------------*/

module_init(hrt_init);
module_exit(hrt_exit);

MODULE_AUTHOR("frog@falinux.com");
MODULE_LICENSE("GPL");

/* end */
