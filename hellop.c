#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

static char* whom = "world";
static int howmany = 1;
module_param(whom, charp, S_IRUGO);
module_param(howmany, int, S_IRUGO);

static int __init initialization(void) {
  for (int i = 0; i < howmany; ++i) {
    printk(KERN_INFO "Hi, %s\n", whom);
  }
  return 0;
}

static void __exit exit_mod(void) {
    printk(KERN_INFO "Goodbye, %s\n", whom);
}

module_init(initialization);
module_exit(exit_mod);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ritwik Singh");
