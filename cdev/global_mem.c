#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
//#include <linux/fs.h>
#include <linux/slab.h> //kzalloc
#include <linux/uaccess.h>  // copy_to_user

#define GLOBALMEM_SIZE 0x1000
#define MEM_CLEAR 0X1
#define GLOBALMEM_MAJOR 230
#define DEVICE_NUM 20

static int globalmem_major = GLOBALMEM_MAJOR;
module_param(globalmem_major, int, S_IRUGO);

typedef struct globalmem_dev {
    struct cdev cdev;
    unsigned char mem[GLOBALMEM_SIZE];
    struct mutex mutex;
} globalmem_dev;

globalmem_dev *globalmem_devp = NULL;

static ssize_t globalmem_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
    unsigned long p = *ppos;
    unsigned int count = size;
    int ret = 0;
    globalmem_dev *dev = filp->private_data;

    if (p >= GLOBALMEM_SIZE)
        return 0;

    if (count > GLOBALMEM_SIZE - p)
        count = GLOBALMEM_SIZE - p;

    mutex_lock(&dev->mutex);
    if (copy_to_user(buf, dev->mem + p, count)) {
        ret = -EFAULT;
	} else {
        *ppos += count;
	    ret = count;
    }
    mutex_unlock(&dev->mutex);

    return ret;
}

static ssize_t globalmem_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
    unsigned long p = *ppos;
    unsigned int count = size;
    int ret = 0;
    globalmem_dev *dev = filp->private_data;

    if (p >= GLOBALMEM_SIZE)
        return 0;

    if (count > GLOBALMEM_SIZE - p)
        count = GLOBALMEM_SIZE - p;

	mutex_lock(&dev->mutex);
    if (copy_from_user(dev->mem + p, buf, count)) {
        ret = -EFAULT;
    } else {
        *ppos += count;
	    ret = count;
    }
	mutex_unlock(&dev->mutex);
    return ret;
}

static loff_t globalmem_llseek(struct file *filp, loff_t offset, int orig)
{
    loff_t ret = 0;

    switch(orig) {
    case SEEK_SET:
	    if (offset < 0 || offset > GLOBALMEM_SIZE) {
	        ret = -EINVAL;
	        break;
		}
	    filp->f_pos = offset;
	    ret = filp->f_pos;
	    break;
    case SEEK_CUR:
	    if (filp->f_pos + offset > GLOBALMEM_SIZE || filp->f_pos + offset < 0) {
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

static int globalmem_open(struct inode *inode, struct file *filp)
{
    globalmem_dev *dev = container_of(inode->i_cdev, globalmem_dev, cdev);
    filp->private_data = dev;

    return 0;
}

static int globalmem_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static long globalmem_ioctl(struct file *filp, unsigned int cmd,
		unsigned long arg)
{
	globalmem_dev *dev = filp->private_data;

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

struct file_operations globalmem_fops = {
    .owner = THIS_MODULE,
    .llseek = globalmem_llseek,
    .open = globalmem_open,
    .release = globalmem_release,
    .unlocked_ioctl = globalmem_ioctl,
    .read = globalmem_read,
    .write = globalmem_write,
};

static void globalmem_setup_cdev(globalmem_dev *dev, int index)
{
    int err;
    int devno = MKDEV(globalmem_major, index);

    if (!dev)
        printk(KERN_ERR "setup globalmem dev failed!\n");

    cdev_init(&dev->cdev, &globalmem_fops);
    err = cdev_add(&dev->cdev, devno, 1);
    if (err)
        printk(KERN_ERR "Error %d add globalmem dev %d!\n", err, index);
}

static int __init globalmem_init(void)
{
    int ret = -1;
    int i = 0;
    dev_t devno = MKDEV(globalmem_major, 0);

    if (globalmem_major) { // static register
        ret = register_chrdev_region(devno, DEVICE_NUM, "globalmem");
    } else {
        ret = alloc_chrdev_region(&devno, 0, DEVICE_NUM, "globalmem");
	    globalmem_major = MAJOR(devno);
    }
    if (ret < 0) {
        printk(KERN_ERR "allocate device number failed\n");
        return ret;
    }

    globalmem_devp = kzalloc(sizeof(globalmem_dev) * DEVICE_NUM, GFP_KERNEL);
    if (!globalmem_devp) {
	    ret = -ENOMEM;
	    goto fail_malloc;
    }

    mutex_init(&globalmem_devp->mutex);

    for (i = 0; i < DEVICE_NUM; i++)
        globalmem_setup_cdev(globalmem_devp + i, i);

    printk(KERN_INFO "Hello globalmem cdev\n");
    return 0;

fail_malloc:
    unregister_chrdev_region(devno, DEVICE_NUM);
    return ret;
}

static void __exit globalmem_exit(void)
{
    int i = 0;
    dev_t devno = MKDEV(globalmem_major, 0);

    for (i = 0; i < DEVICE_NUM; i++)
        cdev_del(&(globalmem_devp + i)->cdev);
    kfree(globalmem_devp);
    unregister_chrdev_region(devno, DEVICE_NUM);
    printk(KERN_INFO "Goodby globalmem cdev\n");
}

module_init(globalmem_init);
module_exit(globalmem_exit);

MODULE_AUTHOR("lidonglin <tjulidonglin@live.cn>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Simple chardev driver");

