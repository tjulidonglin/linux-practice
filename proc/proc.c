/**
 *proc fs example
 *Author: LiDonglin
 *Date: 2020/01/01
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>

static unsigned long variable;
static struct proc_dir_entry *test_dir, *test_entry;

static ssize_t test_proc_read(struct file *file, char __user *buffer, size_t count,
		loff_t *off)
{
	put_user(buffer, &variable);
    return count;
}

static ssize_t test_proc_write(struct file *file, const char __user *buffer, size_t count,
		loff_t *off)
{
	variable = simple_strtoul(buffer, NULL, 10);

	return count;
}

static int test_proc_open(struct inode * inode, struct file * file)
{
	file->private_data = &variable;

	return 0;
}

static const struct file_operations test_proc_fops = {
	.owner = THIS_MODULE,
	.open = test_proc_open,
	.read = test_proc_read,
	.write = test_proc_write,
};

static int __init test_proc_init(void)
{
	test_dir = proc_mkdir("test_dir", NULL);
	if (test_dir) {
		test_entry = proc_create_data("test_rw", 0666, test_dir, &test_proc_fops, NULL);
		if (test_entry) {
//			test_entry->nlink = 1;
//			test_entry->data = &variable;
//			test_entry->read_proc = test_proc_read;
//			test_entry->write_proc = test_proc_write;
			return 0;
		}
	}

	return -ENOMEM;
}

static void __exit test_proc_cleanup(void)
{
	remove_proc_entry("test_rw", test_dir);
	remove_proc_entry("test_dir", NULL);
}

module_init(test_proc_init);
module_exit(test_proc_cleanup);

MODULE_AUTHOR("lidonglin <tjulidonglin@live.cn>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Simple chardev driver");

