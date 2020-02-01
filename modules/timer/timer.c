/**
 *Test timer_list
 *Author: LiDonglin
 *Date: 2019/12/15
 */
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h> //kzalloc
#include <linux/uaccess.h>  // copy_to_user

#define second_MAJOR 230

static int second_major = second_MAJOR;
module_param(second_major, int, S_IRUGO);

struct second_dev {
    struct cdev cdev;
    atomic_t counter;
    struct timer_list s_timer;
};

static struct second_dev *second_devp;

static void second_timer_handler(struct timer_list *arg)
{
    mod_timer(&second_devp->s_timer, jiffies + HZ);
    atomic_inc(&second_devp->counter);
    printk(KERN_INFO "current jiffies is %ld\n", jiffies);
}

static ssize_t second_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
    int counter;

	counter = atomic_read(&second_devp->counter);
	if (put_user(counter, (int*)buf))
		return -EFAULT;
	else
        return sizeof(unsigned int);
}

static int second_open(struct inode *inode, struct file *filp)
{
	timer_setup(&second_devp->s_timer, second_timer_handler, 0);
	//second_devp->s_timer.function = &second_timer_handler;
	second_devp->s_timer.expires = jiffies + HZ;
	add_timer(&second_devp->s_timer);
	atomic_set(&second_devp->counter, 0);
    return 0;
}

static int second_release(struct inode *inode, struct file *filp)
{
    del_timer(&second_devp->s_timer);
    return 0;
}

struct file_operations second_fops = {
    .owner = THIS_MODULE,
    .open = second_open,
    .release = second_release,
    .read = second_read,
};

static void second_setup_cdev(struct second_dev *dev, int index)
{
    int err;
    int devno = MKDEV(second_major, index);

    if (!dev)
        printk(KERN_ERR "setup second dev failed!\n");

    cdev_init(&dev->cdev, &second_fops);
    dev->cdev.owner = THIS_MODULE;
    err = cdev_add(&dev->cdev, devno, 1);
    if (err)
        printk(KERN_ERR "Error %d add second dev %d!\n", err, index);
}

static int __init second_init(void)
{
    int ret;
    dev_t devno = MKDEV(second_major, 0);

    if (second_major) { // static register
        ret = register_chrdev_region(devno, 1, "second");
    } else {
        ret = alloc_chrdev_region(&devno, 0, 1, "second");
	    second_major = MAJOR(devno);
    }
    if (ret < 0) {
        printk(KERN_ERR "allocate device number failed\n");
        return ret;
    }

    second_devp = kzalloc(sizeof(*second_devp), GFP_KERNEL);
    if (!second_devp) {
	    ret = -ENOMEM;
	    goto fail_malloc;
    }

    second_setup_cdev(second_devp, 0);

    printk(KERN_INFO "Hello second cdev\n");
    return 0;

fail_malloc:
    unregister_chrdev_region(devno, 1);
    return ret;
}

static void __exit second_exit(void)
{
    dev_t devno = MKDEV(second_major, 0);

    cdev_del(&second_devp->cdev);
    kfree(second_devp);
    unregister_chrdev_region(devno, 1);
    printk(KERN_INFO "Goodby second cdev\n");
}

module_init(second_init);
module_exit(second_exit);

MODULE_AUTHOR("lidonglin <tjulidonglin@live.cn>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Simple chardev driver");

