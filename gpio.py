#!/usr/bin/env python
# encoding: utf-8
# File Name: gpio.py
# Author: Fang Yuan (yfang@nju.edu.cn)
# Created Time: Wed 18 Jan 2017 09:30:28 PM CST
# GPIO library


import struct


class GPIO:
    def __init__(self, file):
        self.gpiofile = open(file, 'wb')

    def setMode(self, pin, mode):
        print pin, mode

    def setPin(self, pin, status):
        if status != 0:
            status = 1
        print "pin, status", pin, status
        c = struct.pack('I', (1 << pin) | status)
        self.gpiofile.write(c)
        self.gpiofile.flush()

    def getPin(pin):
        c = self.gpiofile.read(4)
        return c
