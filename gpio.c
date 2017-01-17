/*
 * ============================================================================
 *
 *       Filename:  gpio.c
 *
 *    Description:  Raspberry PI GPIO driver
 *
 *        Version:  1.0
 *        Created:  01/17/2017 06:43:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Yuan (yfang@nju.edu.cn)
 *   Organization:  nju
 *
 * ============================================================================
 */

#include <linux/kernel.h>
#include <linux/module.h>
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

volatile int *gpio;

int gpio_open(struct inode *inode, struct file *filp)
{
    int val, i, n, shift;

    /* Set first 28 pins (except 0,1,14,15) as output */
    for (i = 0; i < 28; i++) {
        if ((i == 0) || (i == 1) || (i == 14) | (i ==15))
            continue;
        n = i / 10;
        shift = (i % 10) * 3;
        val = *(int *)(gpio + n*4);
        val &= ~(0b111 << shift);
        val |= (0b001 << shift);
        *(int *)(gpio + n*4) = val;
    }

    printk("file opened\n");
    return 0;
}

int gpio_close (struct inode *inode, struct file *filp)
{
    return 0;
}

ssize_t gpio_read (struct file *filp,
                  char __user *buf,
                  size_t size,
                  loff_t *offset)
{
    int val, n, opsize;
    
    if (size > 8)  size = 8;
    val = *(int *)(gpio + GPLEV0);
    if(size >= 4) {
        n = copy_to_user(buf, &val, 4);
        opsize = (4 - n);
    } else {
        n = copy_to_user(buf, &val, size);
        opsize = (size - n);
    }

    size -= 4;
    if (size > 0) {
        val = *(int *)(gpio + GPLEV1);
        n = copy_to_user(buf+opsize, &val, size);
        opsize += (size - n);
    }
    return opsize;
}

ssize_t gpio_write (struct file *filp,
                   const char __user *buf,
                   size_t size,
                   loff_t *offset)
{
    int val, set, clr, n, opsize;

    if (size > 8)  size = 8;
    val = 0;
    if (size >= 0) {
        n = copy_from_user(&val, buf, 4);
        opsize = (4 - n);
    } else {
        n = copy_from_user(&val, buf, size);
        opsize = (size - n);
    }
        printk("write val=%x\n", val);
    set = val;
    clr = ~val;
    *(int *)(gpio + GPSET0) = set;
    *(int *)(gpio + GPCLR0) = clr;
    
    size -= 4;
    if (size > 0) {
        n = copy_from_user(&val, buf, size);
        opsize += (size -n);
    }
        printk("write val=%x\n", val);
    set = val;
    clr = ~val;
    *(int *)(gpio + GPSET1) = set;
    *(int *)(gpio + GPCLR1) = clr;

    return opsize;
}


/* IOCTL set GPIO0-31 direction. 0 as INPUT, 1 as OUTPUT */
long gpio_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    switch (cmd) {
        case GPIOSETIN:
            break;
        case GPIOSETOUT:
            break;
        default:
            break
    }
    return 0;
}

struct file_operations fop={
    .open    = gpio_open,
    .release = gpio_close,
    .read    = gpio_read,
    .write   = gpio_write,
    .unlocked_ioctl = gpio_ioctl,
};

int init_module(void)
{
    int val;

    val = register_chrdev(223, "GPIO driver", &fop);
    gpio = ioremap(GPIOBASE, 0x40*4); // Less than 64 32-bit registers

    printk ("GPIO-> %p", gpio);
    printk("GPIO driver installed\n");
	return 0;
}

void cleanup_module(void)
{
    iounmap(gpio);

    unregister_chrdev(223, "GPIO driver");
    printk("GPIO driver removed\n");
}

MODULE_LICENSE("GPL");
