#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>

//MODULE_LICENCE("GPLv2");
MODULE_AUTHOR("Chpeckdev");

static int VAR_INT_TEST = 1;
static char *VAR_CHAR_TEST = "FIRST CONDITION";

module_param (VAR_INT_TEST, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(VAR_INT_TEST, "First int variable");
module_param (VAR_CHAR_TEST, charp, 0000);
MODULE_PARM_DESC(VAR_CHAR_TEST, "First char variable");

int init_module(void) {
	printk(KERN_ALERT "HI MAN, I'm kernel module\n\r");
	printk(KERN_ALERT "INT: %d\n\r", VAR_INT_TEST);
	printk(KERN_ALERT "CHAR: %s\n\r", VAR_CHAR_TEST);
	return 0;
}

void cleanup_module(void) {
	printk(KERN_ALERT "CLEANUP SUCCESFULLY\n\r");
}
