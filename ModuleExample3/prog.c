//In comments -> CD means character device

#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

//  Max number of minor devices
#define MAX_DEV 2

//  function declarations
static int charDevSSD_open(struct inode *inode, struct file *file);
static int charDevSSD_release(struct inode *inode, struct file *file);
static long charDevSSD_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static ssize_t charDevSSD_read(struct file *file, char __user *buf, size_t count, loff_t *offset);
static ssize_t charDevSSD_write(struct file *file, const char __user *buf, size_t count, loff_t *offset);

//  bind required file operations
static const struct file_operations charDevSSD_fops = {
    .owner      = THIS_MODULE,
    .open       = charDevSSD_open,
    .release    = charDevSSD_release,
    .unlocked_ioctl = charDevSSD_ioctl,
    .read       = charDevSSD_read,
    .write       = charDevSSD_write
};

//  To keep data related to the device
struct device_data {
    struct cdev charDev;
};

//  To keep major number
static int major_num = 0;

//  Sysfs class structure
static struct class *charDevSSD_class = NULL;

//  To keep all newly created devices' data
static struct device_data charDevSSD_data[MAX_DEV];

//  To give permissions
static int charDevSSD_uevent(struct device *dev, struct kobj_uevent_env *env)
{
    add_uevent_var(env, "DEVMODE=%#o", 0666);
    return 0;
}


static int __init charDevSSD_init(void)
{
    int err, i;
    dev_t device;

    /*  Allocate and register the range of char device numbers
    **      dev -> output
    **      0 -> first (minimum) minor number
    **      MAX_DEV -> number of minor numbers (number of subdevices)
    **      "charDevSSD" -> name of the device
    */
    err = alloc_chrdev_region(&device, 0, MAX_DEV, "charDevSSD");

    //  Get the major number of the device
    major_num = MAJOR(device);


    for (i = 0; i < MAX_DEV; i++) {
        cdev_init(&charDevSSD_data[i].charDev, &charDevSSD_fops);
        charDevSSD_data[i].charDev.owner = THIS_MODULE;

        /*  To add the device to the system
        **      i -> Minor number
        */  
        cdev_add(&charDevSSD_data[i].charDev, MKDEV(major_num, i), 1);

        /*  To create the device
        **      Example device name: charDeviceSSD-[i]
        */ 
        device_create(charDevSSD_class, NULL, MKDEV(major_num, i), NULL, "charDeviceSSD-%d", i);
    }

    //  Create sysfs class
    charDevSSD_class = class_create(THIS_MODULE, "charDeviceSSD");

    //  Assign permissions
    charDevSSD_class->dev_uevent = charDevSSD_uevent;

    return 0;
}

//  To destroy CD if it's not longer needed
static void __exit charDevSSD_exit(void)
{
    int i;

    for (i = 0; i < MAX_DEV; i++) {
        device_destroy(charDevSSD_class, MKDEV(major_num, i));
    }

    class_unregister(charDevSSD_class);
    class_destroy(charDevSSD_class);

    unregister_chrdev_region(MKDEV(major_num, 0), MINORMASK);
}

static int charDevSSD_open(struct inode *inode, struct file *file)
{
    printk("CHARDEVICESSD: Device open\n");
    return 0;
}

static int charDevSSD_release(struct inode *inode, struct file *file)
{
    printk("CHARDEVICESSD: Device close\n");
    return 0;
}

static long charDevSSD_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk("CHARDEVICESSD: Device ioctl\n");
    return 0;
}

static ssize_t charDevSSD_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    uint8_t *data = "Hello from the kernel world!\n";
    size_t datalen = strlen(data);

    printk("Reading device: %d\n", MINOR(file->f_path.dentry->d_inode->i_rdev));

    if (count > datalen) {
        count = datalen;
    }

    if (copy_to_user(buf, data, count)) {
        return -EFAULT;
    }

    return count;
}

static ssize_t charDevSSD_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    size_t maxdatalen = 30, ncopied;
    uint8_t databuf[maxdatalen];

    printk("Writing device: %d\n", MINOR(file->f_path.dentry->d_inode->i_rdev));

    if (count < maxdatalen) {
        maxdatalen = count;
    }

    ncopied = copy_from_user(databuf, buf, maxdatalen);

    if (ncopied == 0) {
        printk("Copied %zd bytes from the user\n", maxdatalen);
    } else {
        printk("Could't copy %zd bytes from the user\n", ncopied);
    }

    databuf[maxdatalen] = 0;

    printk("Data from the user: %s\n", databuf);

    return count;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Suleyman Semih Demir <ssdmail123456@ssd.com>");

module_init(charDevSSD_init);
module_exit(charDevSSD_exit);