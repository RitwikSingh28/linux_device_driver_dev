#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>

#define DEVICE_NAME "example_device"

static dev_t dev;
static int __init register_module(void) {
  int ret;

  ret = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
  if (ret < 0) {
    printk(KERN_ERR "Failed to allocate device number");
    return ret;
  }

  printk(KERN_INFO "Allocated Major: %d Minor: %d\n", MAJOR(dev), MINOR(dev));
  return 0;
}

static void __exit unregister_module(void) {
  unregister_chrdev_region(dev, 1);
  printk(KERN_INFO "Device number unregistered\n");
}

module_init(register_module);
module_exit(unregister_module);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ritwik Singh");
