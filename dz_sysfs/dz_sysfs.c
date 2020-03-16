#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/string.h>

MODULE_AUTHOR("Chpeckdev");
MODULE_LICENSE("GPL");

static struct kobject *chpeck_module;

static int chpeck_var = 0;

static ssize_t chpeck_var_show(struct kobject* kobj, struct kobj_attribute* attr, char* buf){
	return sprintf(buf, "%d\n", chpeck_var);
}

static ssize_t chpeck_var_store(struct kobject* kobj, struct kobj_attribute* attr, char* buf, size_t count){
	sscanf(buf,"%du", &chpeck_var);
	return count;
}

static struct kobj_attribute chpeck_var_attribute = __ATTR(chpeck_var, 0660, chpeck_var_show,(void*)chpeck_var_store);

static int __init chpeck_module_init(void){
	int retn = 0;
	pr_info("chpeck_module init...\n\r");
	chpeck_module = kobject_create_and_add("chpeck_module", kernel_kobj);
	if (!chpeck_module){
		return -ENOMEM;
	}
	retn = sysfs_create_file(chpeck_module, &chpeck_var_attribute.attr);
	if (retn){
		pr_info("FAILED to create chpeck_var file...\n\r");
	}
	return retn;
}

static void __exit chpeck_module_exit(void){
	pr_info("chpeck_module exit...\n\r");
	kobject_put(chpeck_module);
}

module_init(chpeck_module_init);
module_exit(chpeck_module_exit);
