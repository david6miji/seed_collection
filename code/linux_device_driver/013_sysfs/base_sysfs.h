/*-----------------------------------------------------------------------------
  file : base_gpio.h
  desc : 
  auth : frog@falinux.com
  date : 2016/09/17
  noty : linux-imx6_3.10.53

-------------------------------------------------------------------------------*/
#ifndef __LINUX_BASE_SYSFS_H
#define __LINUX_BASE_SYSFS_H

struct frog {
	char              	name[128];
	struct device       *dev;
	struct list_head    list;
	char 				value[128];
};

#endif  // __LINUX_BASE_SYSFS_H
