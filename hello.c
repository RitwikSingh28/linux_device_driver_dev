#include "linux/printk.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ritwik Singh");
MODULE_DESCRIPTION("Hello world module");
MODULE_VERSION("0.1");

static int __init hello_init(void) {
  printk(KERN_INFO "Heiee\n");
  printk(KERN_INFO "Hello World!\n");
  printk(KERN_INFO "pid: %i\n", current->pid);
  return 0;
}

static void __exit hello_exit(void) {
  printk(KERN_INFO "Goodbye World\n");
}

module_init(hello_init);
module_exit(hello_exit);
