/*
 * A simple char device driver: globalmem without mutex
 * 
 * Copyright (C) 2014 lidonglin (lidonglin@huaewi.com)
 *
 * Licensed under GPLv2 or later  
*/

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define GLOBALMEM_SIZE 0x1000
#define MEM_CLEAR 0x1
#define GLOBALMEM_MAJOR 230
#define DEVICE_NUM 10

static int globalmem_major = GLOBALMEM_MAJOR;
module_param(globalmem_major, int, S_IRUGO);

struct globalmem_dev {
    struct cdev cdev;
    unsigned char mem[GLOBALMEM_SIZE];
    struct mutex mutex;
    unsigned int current_len;
    wait_queue_head_t r_wait;
    wait_queue_head_t w_wait;
};

struct globalmem_dev *globalmem_devp;

static loff_t globalmem_llseek(struct file *filp, loff_t offset, int orig)
{
    loff_t ret = 0;

    switch (orig) {
    case 0:
        if (offset < 0) {
            ret = -EINVAL;
            break;
        }

        if ((unsigned int)offset > GLOBALMEM_SIZE) {
            ret = -EINVAL;
            break;
        }

        filp->f_pos = (unsigned int)offset;
        ret = filp->f_pos;
        break;
    case 1:
        if ((filp->f_pos + offset) > GLOBALMEM_SIZE) {
            ret = -EINVAL;
            break;
        }

        if (filp->f_pos + offset < 0) {
            ret = -EINVAL;
            break;
        }

        filp->f_pos += offset;
        ret = filp->f_pos;
        break;

    default:
        ret = -EINVAL;
        break;
    }

    return ret;
}

static ssize_t globalmem_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
    int ret = 0;
    struct globalmem_dev *dev = filp->private_data;
    DECLARE_WAITQUEUE(wait, current);

    mutex_lock(&dev->mutex);
    add_wait_queue(&dev->r_wait, &wait);

    while (dev->current_len == 0) {
        if (filp->f_flags & O_NONBLOCK) {
            ret = -EAGAIN;
            goto out;
        }

        /* for block IO, let process sleep */
        __set_current_state(TASK_INTERRUPTIBLE);
        mutex_unlock(&dev->mutex);
        schedule();

        /* after process is waked up */
        if (signal_pending(current)) {
            ret = -ERESTARTSYS;
            goto out2;
        }

        mutex_lock(&dev->mutex);
    }

    if (count > dev->current_len)
        count = dev->current_len;

    if (copy_to_user(buf, dev->mem, count)) {
        ret = -EFAULT;
        goto out;
    } else { 
        /* invalid read bytes from fifo and update current_len */
        memcpy(dev->mem, dev->mem + count, dev->current_len - count);
        dev->current_len -= count;
        printk(KERN_INFO"read %lu bytes(s), current_len: %u\n", count, dev->current_len);

        /* wake up write process */
        wake_up_interruptible(&dev->w_wait);

        ret = count;
    }

out:
    mutex_unlock(&dev->mutex);
out2:
    remove_wait_queue(&dev->r_wait, &wait);
    set_current_state(TASK_RUNNING);
    return ret;
}

static ssize_t globalmem_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
    int ret = 0;
    struct globalmem_dev *dev = filp->private_data;
    DECLARE_WAITQUEUE(wait, current);

    mutex_lock(&dev->mutex);
    add_wait_queue(&dev->w_wait, &wait);

    while (dev->current_len == GLOBALMEM_SIZE) {
        /* for nonblock io */
        if (filp->f_flags & O_NONBLOCK) {
            ret = -EAGAIN;
            goto out;
        }

        /* for block io, let process sleep */
        __set_current_state(TASK_INTERRUPTIBLE);
        mutex_unlock(&dev->mutex);
        schedule();

        /* waked up by signal */
       if (signal_pending(current)) {
           ret = -ERESTARTSYS;
           goto out2;
       }

       mutex_lock(&dev->mutex);
    }

    if (count > GLOBALMEM_SIZE - dev->current_len)
        count = GLOBALMEM_SIZE - dev->current_len;

    if (copy_from_user(dev->mem + dev->current_len, buf, count)) {
        ret = -EFAULT;
        goto out;
    } else {
        /* update current_len */
        dev->current_len += count;
        ret = count;
        printk(KERN_INFO"written %lu byte(s), current_len:%u\n", count, dev->current_len);
        /* wake up read queue */
        wake_up_interruptible(&dev->r_wait);
    }

out:
    mutex_unlock(&dev->mutex);
out2:
    remove_wait_queue(&dev->w_wait, &wait);
    set_current_state(TASK_RUNNING); 
    return ret;
}

static long globalmem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    struct globalmem_dev *dev = filp->private_data;

    switch(cmd) {
    case MEM_CLEAR:
        mutex_lock(&dev->mutex);
        memset(dev->mem, 0, GLOBALMEM_SIZE);
        mutex_unlock(&dev->mutex);
        printk(KERN_INFO"globalmem is set to zero\n");
        break;

    default:
        return -EINVAL;
    }
    return 0;
}

static int globalmem_open(struct inode *inode, struct file *filp)
{
    struct globalmem_dev *dev = container_of(inode->i_cdev, struct globalmem_dev, cdev);

    filp->private_data = dev;
    return 0;
}

static int globalmem_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static const struct file_operations globalmem_fops = {
    .owner = THIS_MODULE,
    .llseek = globalmem_llseek,
    .read = globalmem_read,
    .write = globalmem_write,
    .unlocked_ioctl = globalmem_ioctl,
    .open = globalmem_open,
    .release = globalmem_release,
};


static void globalmem_setup_cdev(struct globalmem_dev *dev, int index)
{
    int err;
    int devno = MKDEV(globalmem_major, index);

    /* step1: initialise cdev */
    cdev_init(&dev->cdev, &globalmem_fops);
    dev->cdev.owner = THIS_MODULE;

    /* setp2: add cdev to kernel */
    err = cdev_add(&dev->cdev, devno, 1);
    if (err)
        printk(KERN_NOTICE"Error %d adding globalmem%d", err, index);
}

static int __init globalmem_init(void)
{
    int ret;
    int i = 0;
    dev_t devno = MKDEV(globalmem_major, 0);

    /* get devno */
    if (globalmem_major)
        ret = register_chrdev_region(devno, DEVICE_NUM, "globalmem");
    else {
        ret = alloc_chrdev_region(&devno, 0, DEVICE_NUM, "globalmem");
        globalmem_major = MAJOR(devno);
    }

    if (ret < 0)
        return ret;

    globalmem_devp = kzalloc(sizeof(struct globalmem_dev) * DEVICE_NUM, GFP_KERNEL);
    if (!globalmem_devp) {
        ret = -ENOMEM;
        goto fail_malloc;
    }

    for (i = 0; i < DEVICE_NUM; i++) {
        struct globalmem_dev *tmp = globalmem_devp + i;

        mutex_init(&tmp->mutex);
        init_waitqueue_head(&tmp->r_wait); 
        init_waitqueue_head(&tmp->w_wait); 
        globalmem_setup_cdev(tmp, i);
    }

    return 0;

fail_malloc:
    unregister_chrdev_region(devno, DEVICE_NUM);
    return ret;
}


static void __exit globalmem_exit(void)
{
    int i;

    for (i = 0; i < DEVICE_NUM; i++) {
        cdev_del(&(globalmem_devp + i)->cdev);
    }
    kfree(globalmem_devp);
    unregister_chrdev_region(MKDEV(globalmem_major, 0), DEVICE_NUM);
}

module_init(globalmem_init);
module_exit(globalmem_exit);
MODULE_AUTHOR("lidonglin <lidonglin@huawei.com>");
MODULE_LICENSE("GPLv2");
