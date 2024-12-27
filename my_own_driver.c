#include "linux/device.h"
#include "linux/device/class.h"
#include "linux/err.h"
#include "linux/fs.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ritwik Singh");
MODULE_DESCRIPTION("This is a sample chrdev tutorial");

dev_t device_number;
#define NUM_DEVICES 1

struct class* class_dev;
struct device* device_dev;

struct cdev my_cdev;

static int example_open(struct inode *inode, struct file *filp) {
  printk(KERN_INFO "OPEN: Open request received\n");
  return 0;
}

static ssize_t example_read(struct file *filp, char __user *buffer, size_t size, loff_t *offset) {
  printk(KERN_INFO "READ: Read request received\n");
  return 0;
}

static ssize_t example_write(struct file *filp, const char __user *buffer, size_t size, loff_t *offset) {
  printk(KERN_INFO "WRITE: Write request received\n");
  return size;
}

struct file_operations fops = {
  .open = example_open,
  .read = example_read,
  .write = example_write,
};

static int __init my_init(void) {
  printk(KERN_INFO "Hello there!\n");

  printk(KERN_INFO "Getting the major/minor numbers\n");

  if (alloc_chrdev_region(&device_number, 0, NUM_DEVICES, "sample_chrdev")) {
    printk(KERN_ERR "Couldn't get the numbers. Bailing out!\n");
    return -1;
  }
  printk(KERN_INFO "Allotted <major>:<minor> = %d:%d\n", MAJOR(device_number), MINOR(device_number));

  printk(KERN_INFO "Initializing chrdev struct...\n");
  cdev_init(&my_cdev, &fops);
  my_cdev.owner = THIS_MODULE;
  printk(KERN_INFO "Initialization Done...\n");

  printk(KERN_INFO "Adding driver to kernel\n");
  if (cdev_add(&my_cdev, device_number, NUM_DEVICES)) {
    printk(KERN_ERR "Failed in registering the driver with the kernel");
    return -1;
  }
  printk(KERN_INFO "Done...\n");

  // Create device class
  class_dev = class_create("sample_class");
  if (IS_ERR(class_dev)) {
    printk(KERN_ERR "Failed in creating the struct class for the device");
  }
  // Populate the sysfs with device information
  device_dev = device_create(class_dev, NULL, device_number, NULL, "sample");
  if (IS_ERR(device_dev)) {
    printk(KERN_ERR "Failed in creating the struct device for the device");
  }

  printk(KERN_INFO "Module init successful...\n");
  return 0;
}

static void __exit my_exit(void) {
  device_destroy(class_dev, device_number);
  class_destroy(class_dev);
  cdev_del(&my_cdev);
  unregister_chrdev_region(device_number, NUM_DEVICES);
  printk(KERN_INFO "Goodbye there!\n");
}

module_init(my_init);
module_exit(my_exit);
