#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

//MODULE_LICENCE("GPLv2");
MODULE_AUTHOR("Chpeckdev");

int init_module(void);
void cleanup_module(void);

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);

static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define DEVICE_NAME "chpeckdev"
#define BUF_LEN 16
#define Major_num 183

static int err;
static int Device_Open = 0;

static char msg[BUF_LEN];
static char *msg_Ptr;

static struct file_operations fo = {
  .read = device_read,
  .write = device_write,
  .open = device_open,
  .release = device_release
};

int init_module(void){
  err = register_chrdev(Major_num, DEVICE_NAME, &fo);
  if (err < 0) {
    printk("Dev failed %d\n",err);
    return err;
  }
  sprintf(msg, "Init_suc!\n");
  return 0;
}

void cleanup_module(void){
  unregister_chrdev(Major_num, DEVICE_NAME);
}

static int device_open(struct inode *inode, struct file *file){
  static int counter = 0;
  if (Device_Open)
    return -EBUSY;
  Device_Open++;
  counter++;
  msg_Ptr = msg;
  try_module_get(THIS_MODULE);
  return 0;
}

static int device_release(struct inode *inode, struct file *file){
  Device_Open--;
  module_put(THIS_MODULE);
  return 0;
}

static ssize_t device_read(struct file *filp, char *buff,  size_t len, loff_t * offset){
  int bytes_read = 0;
  if (*msg_Ptr == 0){
    return 0;
  }
  while (len && *msg_Ptr){
    put_user(*(msg_Ptr++), buff++);
    len--;
    bytes_read++;
  }
  return bytes_read;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off){
  if (len > BUF_LEN){
    return -EINVAL;
  }
  int i;
  memset(msg, 0, BUF_LEN);
  for (i = 0; i < len && i < BUF_LEN; i++){
    get_user(msg[i], buff + i);
  }
  return i;
}
