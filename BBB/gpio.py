#!/usr/bin/env python
# encoding: utf-8
# File Name: gpio.py
# Author: Fang Yuan (yfang@nju.edu.cn)
# Created Time: Wed 18 Jan 2017 09:30:28 PM CST
# GPIO library

GPIO_ROOT = '/sys/class/gpio'
# write a number(string) to /sys/class/gpio/export will create
# the corresponding gpio node. write a number to /sys/class/gpio/unexport 
# delete the node

# when gpio pin opened, write 'high' or 'low' to gpioXX/direction
# will set the pin function as OUTPUT or INPUT
# gpioXX/value is used to set or get pin level

class GPIO:
    def __init__(self, pin, dir):
        f = open(GPIO_ROOT+'/unexport', 'w')
        try:
            f.write(str(pin))
        except:
            pass
        f.close()    # try close opened GPIO

        f = open(GPIO_ROOT+'/export', 'w')
        try:
            f.write(str(pin))
        except:
            pass
        f.close()
        f = open(GPIO_ROOT+'/gpio'+str(pin)+'/direction', 'w')
        f.write(dir)
        f.close()

    def setPin(self, status):
        pass       # not implemented yet

    def getPin(pin):
        c = self.gpio.read()
        return c
