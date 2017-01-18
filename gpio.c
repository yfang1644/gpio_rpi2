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
        n = i / 10;
        shift = (i % 10) * 3;
        val = gpio[n];
        val &= ~(0b111 << shift);
        val |= (0b001 << shift);
        gpio[n] = val;
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
    int val, n;
    
    val = gpio[GPLEV0];
    n = copy_to_user(buf, &val, 4);

    return 4;
}


/* Set certain pins to "0" or "1". Bit31 is used to identify "SET/CLR"
 */
ssize_t gpio_write (struct file *filp,
                   const char __user *buf,
                   size_t size,
                   loff_t *offset)
{
    int val, n;

    n = copy_from_user(&val, buf, 4);
    if (val & 0x80000000) {
        val &= 0x7FFFFFFF;
        gpio[GPSET0] = val;
    } else {
        gpio[GPCLR0] = val;
    }
    printk("write val=%X\n", val);

    return size;
}


/* IOCTL set LSB32 of GPIO direction in "args". "1" to set, "0" to ignore */
/* upper 22 pins not available in PINout */
long gpio_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int i, val;
    int regs, indx;   /* register and index */

    switch (cmd) {
        case GPIOSETIN:
            for (i = 0; i < 32; i++) {
                if(arg & 1) {
                    regs = i / 10;
                    indx = (i % 10) * 3;
                    val = gpio[regs];
                    val &= ~(0b111 << indx);
                    val |= 0b000 << indx;
                    gpio[regs] = val;
                }
                arg >>= 1;
            }
            break;
        case GPIOSETOUT:
            for (i = 0; i < 32; i++) {
                if(arg & 1) {
                    regs = i / 10;
                    indx = (i%10) * 3;
                    val = gpio[regs];
                    val &= ~(0b111 << indx);
                    val |= 0b001 << indx;
                    gpio[regs] = val;
                }
                arg >>= 1;
            }
            break;
        default:
            break;
    }
    return 0;
}

struct file_operations fop= {
    .open    = gpio_open,
    .release = gpio_close,
    .read    = gpio_read,
    .write   = gpio_write,
    .unlocked_ioctl = gpio_ioctl,
};

int init_module(void)
{
    int val;

    val = register_chrdev(GPIO_MAJOR, "GPIO driver", &fop);
    gpio = ioremap(GPIOBASE, 0x40);    // Less than 41 32-bit registers

    printk ("GPIO-> %p", gpio);
    printk("GPIO driver installed\n");
	return 0;
}

void cleanup_module(void)
{
    iounmap(gpio);

    unregister_chrdev(GPIO_MAJOR, "GPIO driver");
    printk("GPIO driver removed\n");
}

MODULE_LICENSE("GPL");
