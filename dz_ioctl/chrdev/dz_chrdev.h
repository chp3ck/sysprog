#ifndef CHRDEV_H
#define CHRDEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM 183
#define IOCTL_SET_MSG _IOW(MAJOR_NUM, 0, char*)
#define IOCTL_GET_MSG _IOR(MAJOR_NUM, 1, char*)
#define DEVICE_NAME "chpeck_dev"
#define DEVICE_FILE_NAME "/dev/chpeck_dev"
#define CHRDEV_BUF_LEN_MSG 128
#define IOCTL_MAX_SIZE 128

#endif
