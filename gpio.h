/*
 * ============================================================================
 *
 *       Filename:  gpio.h
 *
 *    Description:  GPIO driver for Raspberry PI2/3 (B+)
 *
 *        Version:  1.0
 *        Created:  01/17/2017 06:01:12 PM
 *       Revision:  none
 *       Compiler: 
 *
 *         Author:  Fang Yuan (yfang@nju.edu.cn)
 *   Organization:  nju
 *
 * ============================================================================
 */

#ifndef _GPIO_H
#define _GPIO_H

/*  There are 54 GPIO pins in BCM2835.
     Outlines of Raspberry PI:

        3V3              1   2          5V
   (SDA1)       GPIO2    3   4          5V
   (SCL1)       GPIO3    5   6			GND 
   (GPIO_GCLK)  GPIO4    7   8   GPIO14  (TXD0)
      GND                9   10  GPIO15  (RXD0)
   (GPIO_GEN0)  GPIO17  11   12  GPIO18  (GPIO_GEN1)
   (GPIO_GEN2)  GPIO27  13   14          GND
   (GPIO_GEN3)  GPIO22  15   16  GPIO23  (GPIO_GEN4)
        3V3             17   18  GPIO24  (GPIO_GEN5)
   (SPI_MOSI)   GPIO10  19   20          GND
   (SPI_MISO)   GPIO9   21   22  GPIO25  (GPIO_GEN6)
   (SPI_SCLK)   GPIO11  23   24  GPIO8   (SPI_CE0_N)
        GND             25   26  GPIO7   (SPI_CE1_N)
                ID_SD   27   28  ID_SC
                GPIO5   29   30         GND 
                GPIO6   31   32  GPIO12
                GPIO13  33   34         GND
                GPIO19  35   36  GPIO16
                GPIO26  37   38  GPIO20
        GND             39   40  GPIO21
*/

/*  The GPIO has 41 registers. Some are used below: */
#define GPIOBASE    (0x3F200000)
#define	GPFSEL0	    (0x00)   /* function select register0 */
#define	GPFSEL1	    (0x04)   /* function select register1 */
#define	GPFSEL2	    (0x08)   /* function select register2 */
#define	GPFSEL3	    (0x0C)   /* function select register3 */
#define	GPFSEL4	    (0x10)   /* function select register4 */
#define	GPFSEL5	    (0x14)   /* function select register5 */

/* Every 3-bits in function select register defines the pin function.
 *      000 = GPIO Pin 9 is an input
 *      001 = GPIO Pin 9 is an output
 *      100 = GPIO Pin 9 takes alternate function 0
 *      101 = GPIO Pin 9 takes alternate function 1
 *      110 = GPIO Pin 9 takes alternate function 2
 *      111 = GPIO Pin 9 takes alternate function 3
 *      011 = GPIO Pin 9 takes alternate function 4
 *      010 = GPIO Pin 9 takes alternate function 5

 So, 54 pins needs 6 fsel register: 
        bit0-2 of FSEL0->GPIO0,
        bit27-29 of FSEL0->GPIO9
        bit0-2 of FSEL1->GPIO10,
        bit0-2 of FSEL5->GPIO50, 
        bit9-11 of FSEL5->GPIO53. etc.
*/
/*  When pins are set as Output, write "1" to GPIO SET regisgter will set
*  the corresponding pin. Write "0" has no effect*/
#define	GPSET0	    (0x1C)   /* bit set 0. GPIO0-31 */
#define	GPSET1	    (0x20)   /* bit set 1. GPIO32-53 */
/*  Write "1" to GPIO CLR register will clear the pin. Write "0" has no effect */
#define	GPCLR0	    (0x28)   /* bit clear 0. GPIO0-31 */
#define	GPCLR1      (0x2C)   /* bit clear 1. GPIO32-53 */

#define	GPLEV0	    (0x34)   /* level holder register 0. GPIO0-31 */
#define	GPLEV1      (0x38)   /* level holder register 1. GPIO32-53 */

#endif // _GPIO_H
