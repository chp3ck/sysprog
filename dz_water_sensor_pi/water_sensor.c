#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include "water_sensor.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("chpeckdev & AZ");

dev_t dev = 0;
static struct class *chardev_class;
static struct cdev chardev_cdev;

static char kernel_buffer[256];

static int __init device_init_module(void);
static void __exit device_exit_module(void);
static int chardev_open(struct inode *inode, struct file *file);
static int chardev_release(struct inode *inode, struct file *file);
static ssize_t chardev_read(struct file *filep, char __user *buf, size_t len, loff_t *off);

static struct file_operations fops ={
	.owner = THIS_MODULE,
	.read = chardev_read
};

static ssize_t chardev_read(struct file *filep, char __user *buf, size_t len, loff_t *off){

	uint8_t water_status = 1;

	gpio_direction_input(WATER_CHECK_GPIO);
	memset(kernel_buffer, '\0', 256);
	water_status = gpio_get_value(WATER_CHECK_GPIO);

	if (water_status==0){
		printk(KERN_INFO "barrel not full, water level status: %d...\n\r", water_status);
		sprintf(kernel_buffer, "barrel not full, water level status: %d...\n\r", water_status);
	} else{
		printk(KERN_INFO "barrel is FULL, water level status: %d, check it!!!\n\r", water_status);
		sprintf(kernel_buffer, "barrel is FULL, water level status: %d, check it!!!\n\r", water_status);
	}
	if (copy_to_user(buf, kernel_buffer, 256)){
		return -EFAULT;
	}
	return 256;
}

static int __init device_init_module(void){

	memset(kernel_buffer, '\0', 256);

	if ((alloc_chrdev_region(&dev, 0, 1, "water_sensor")) < 0){
		printk(KERN_ALERT "MAJOR CREATION ERROR!!!");
		return -1;
	}
	printk(KERN_INFO "water sensor string & column in the kernel symtab: %d %d\n\r", MAJOR(dev), MINOR(dev));
	cdev_init(&chardev_cdev, &fops);
	if ((cdev_add(&chardev_cdev, dev, 1)) < 0){
		printk(KERN_ALERT "DEVICE ADD ERROR!!!\n\r");
		unregister_chrdev_region(dev, 1);
		return -1;
	}
	if ((chardev_class = class_create(THIS_MODULE, "water_class")) == NULL){
		printk(KERN_ALERT "DEVICE CLASS CREATION ERROR!!!\n\r");
		unregister_chrdev_region(dev, 1);
		return -1;
	}
	if ((device_create(chardev_class, NULL, dev, NULL, "water_device")) == NULL){
		printk(KERN_ALERT "DEVICE CREATION ERROR!!!\n\r");
		class_destroy(chardev_class);
	}
	printk(KERN_INFO "water device was created...\n\r");
	return 0;
}

static void __exit device_exit_module(void){
	gpio_set_value(WATER_CHECK_GPIO, 0);
	gpio_free(WATER_CHECK_GPIO);
	device_destroy(chardev_class, dev);
	class_destroy(chardev_class);
	cdev_del(&chardev_cdev);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "water device was removed...\n\r");
}

module_init(device_init_module);
module_exit(device_exit_module);
