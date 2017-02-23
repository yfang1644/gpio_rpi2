/*
 * ============================================================================
 *
 *       Filename:  gpio.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/08/2016 10:36:09 AM
 *       Revision:  none
 *       Compiler: 
 *
 *         Author:  Fang Yuan (yfang@nju.edu.cn)
 *   Organization:  nju
 *
 * ============================================================================
 */

/*  P9P9P9P9P9P9P9P9P9P9P9P9P9          P8P8P8P8P8P8P8P8P8P8P8P8P8P8P8P8
         DGND  1    2   DGND                  GND  1    2   GND
         3.3V  3    4   3.3V                GP1_6  3    4   GP1_7
        Vdd5V  5    6   Vdd5V               GP1_2  5    6   GP1_3
        Sys5V  7    8   Sys5V                TMR4  7    8   TMR7 
      PWR_BUT  9    10  RESET                TMR5  9    10  TMR6
       U4_RXD  11   12  GP1_28             GP1_13  11   12  GP1_12
       U4_TXD  13   14  EHRPWM             EHRPWM  13   14  GP0_26
       GP1_16  15   16  EHRPWM             GP1_15  15   16  GP1_14
     I2C1_SCL  17   18  I2C1_SDA           GP0_27  17   18  GP2_1
     I2C2_SCL  19   20  I2C2_SDA           EHRPWM  19   20  GP1_31 
       U2_TXD  21   22  U2_RXD             GP1_30  21   22  GP1_5
       GP1_17  23   24  U1_TXD             GP1_4   23   24  GP1_1 
       GP3_21  25   26  U1_RXD             GP1_0   25   26  GP1_29
       GP3_19  27   28  SP1_CS             GP2_22  27   28  GP2_24
       SP1_D0  29   30  SP1_D1             GP2_23  29   30  GP2_25
      SP1_CLK  31   32  VADC               U5_CTS  31   32  U5_RTS
         AIN4  33   34  AGND               U4_RTS  33   34  U3_RTS
         AIN6  35   36  AIN5               U4_CTS  35   36  U3_CTS
         AIN2  37   38  AIN3               U5_TXD  37   38  U5_RXD
         AIN0  39   40  AIN1               GP2_12  39   40  GP2_13
       CLKOUT  41   42  GP0_7              GP2_10  41   42  GP2_11
         DGND  43   44  DGND               GP2_8   43   44  GP2_9
         DGND  45   46  DGND               GP2_6   45   46  GP2_7
  P9P9P9P9P9P9P9P9P9P9P9P9P9          P8P8P8P8P8P8P8P8P8P8P8P8P8P8P8P8
*/
#ifndef _GPIO_H
#define _GPIO_H

#include <linux/ioctl.h>

typedef struct gpio {
    volatile unsigned int *port;
    volatile unsigned int *ctrl;
} gpio_t;

ssize_t led_read (struct file *filp,
                  char __user *buf,
                  size_t size,
                  loff_t *offset);

#define GPIO0   0x48E07000
#define GPIO1   0x4804c000
#define GPIO1_0 0x800			/* First pin of GPIO1 */
#define GPIO2   0x481AC000
#define GPIO2_0 0x888			/* First pin of GPIO2 */

#define GPIO3   0x481AE000

#define CTRL    (0x130/4)		/* GPIO control register */
#define	OE		(0x134/4)		/* Input/Output select. 0 as output */
#define	DATIN	(0x138/4)
#define DATOUT	(0x13c/4)
#define	CLR     (0x190/4)
#define SET     (0x194/4)

#define CONTRL	0x44e10000

#define	DEVICE_NAME		"/dev/gpio_led"

#define		LEDIOSET	_IOW(221, 0, int)
#define		LEDIOGET	_IOR(221, 0, int)

#endif  // _GPIO_H
