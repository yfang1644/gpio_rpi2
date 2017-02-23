/*
 * ============================================================================
 *
 *       Filename:  gpio.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/08/2016 10:35:57 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Yuan (yfang@nju.edu.cn)
 *   Organization:  nju
 *
 * ============================================================================
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#include "gpio.h"

#ifdef DEBUG
#define PRINT   printk
#else
#define PRINT   
#endif

int led_open (struct inode *inode, struct file *filp)
{
    int i;
    gpio_t *gpio;
    filp->private_data = kmalloc(sizeof(gpio_t), GFP_KERNEL);
    gpio = (gpio_t *)filp->private_data;

    gpio->ctrl = ioremap(CONTRL, 128*1024);
    gpio->port= ioremap(GPIO2, 4096);
    gpio->port[CTRL] = 0;
    for(i = 0; i < 12; i++)  /* set gpio2_1 ... gpio2_17 */
        gpio->ctrl[(0x8a0/4) + i] = 0x37;

    gpio->port[OE] = 0x00000000;  /* set gpio2 as output */
    for(i = 0; i < 10; i++) {
        gpio->port[CLR] = 0x3c0;
        mdelay(1000);
        gpio->port[SET] = 0x3c0;
        mdelay(1000);
    }
    return 0;
}

int led_close (struct inode *inode, struct file *filp)
{
    gpio_t *gpio;

    gpio = (gpio_t *)filp->private_data;
    iounmap(gpio->port);
    iounmap(gpio->ctrl);

    kfree(filp->private_data);

    return 0;
}

ssize_t led_read (struct file *filp,
                  char __user *buf,
                  size_t size,
                  loff_t *offset)
{
    int val, n;
    gpio_t *gpio = (gpio_t *)filp->private_data;

    val = gpio->port[DATIN];
    n = copy_to_user(buf, &val, sizeof(val));

    return size;
}

ssize_t led_write (struct file *filp,
                   const char __user *buf,
                   size_t size,
                   loff_t *offset)
{
    int val, n;
    gpio_t *gpio = (gpio_t *)filp->private_data;

    n = copy_from_user(&val, buf, size);
    if (size > 4)  size = 4;

    gpio->port[DATOUT] = val;   /* Direct set GPIO pin level */

    printk("%p %x\n", &gpio->port[DATOUT], val);
    return size;
}

long led_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    gpio_t *gpio = (gpio_t *)filp->private_data;
    int val, n;
    switch(cmd) {
    case LEDIOSET:
        n = copy_from_user(&val, (unsigned int *)arg, 4);
        gpio->port[OE] = val;
        break;
    case LEDIOGET:
        val = gpio->port[OE];
        n = copy_to_user((unsigned int *)arg, &val, 4);
        break;
    default:
        break;
    }
    return 0;
}

struct file_operations fop={
    .open    = led_open,
    .release = led_close,
    .read    = led_read,
    .write   = led_write,
    .unlocked_ioctl = led_ioctl,

};

int init_module(void)
{
    int val;

    val = register_chrdev(223, "gpio LED", &fop);
    printk("Module installed\n");
	return 0;
}

void cleanup_module(void)
{
    unregister_chrdev(223, "gpio LED");
    printk("module removed from kernel\n");
}

MODULE_LICENSE("GPL");
