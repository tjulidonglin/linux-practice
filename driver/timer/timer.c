#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>


static int sec = 5;
module_param(sec, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(sec, "set timer's interval");
static void mymod_timer(unsigned long data);
static DEFINE_TIMER(timer, mymod_timer, 0, 0);

static void mymod_timer(unsigned long data)
{
    printk(KERN_INFO"mymod_timer: revoke timer\n");
    mod_timer(&timer, jiffies + sec * HZ);
}

static int timer_init(void)
{
    printk(KERN_INFO"timer module inits\n");
    mod_timer(&timer, jiffies + sec * HZ);

    return 0;
}

static void timer_exit(void)
{
    printk(KERN_INFO"timer module exits\n");
    del_timer(&timer);
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_AUTHOR("lidonglin <lidonglin@huaweicom>");
MODULE_DESCRIPTION("simple timer learning module, show how to use timer");
MODULE_LICENSE("GPL");
