#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mark Dehus <mark.dehus@colorado.edu>");
MODULE_DESCRIPTION("In-kernel phase reverser");

static unsigned long buffer_size = 8192;
module_param(buffer_size, ulong, (S_IRUSR | S_IRGRP | S_IROTH));

static struct miscdevice reverse_misc_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "reverse",
    .fops = &reverse_fops
};

static struct file_operations reverse_fops = {
    .owner = THIS_MODULE,
    .open = reverse_open,
    .read = reverse_read,
    .write = reverse_write,
    .release = reverse_close,
    .llseek = noop_llseek
};

struct buffer {
    char *data, *end, *read_ptr;
    unsigned long size;
}

static struct buffer *buffer_alloc(unsigned long size)
{
    struct buffer *buf;
        buf = kzalloc(sizeof(*buf), 
}

static int __init reverse_init()
{
    if (!buffer_size)
        return -1;
    misc_register(&reverse_mics_device);
    printk(KERN_INFO
        "reverse device has been registered, buffer size is %lu bytesn",
        buffer_size);
    return 0;
}

static void __exit reverse_exit(void)
{
    misc_deregister(&reverse_misc_device);
    printk(KERN_INFO "reverse device has been unregisteredn");
}
 

module_init(reverse_init);
module_exit(reverse_exit);
