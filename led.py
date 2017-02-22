#!/usr/bin/env python
# encoding: utf-8
# File Name: led.py
# Author: Fang Yuan
# Mail: yfang@nju.edu.cn
# Created Time: Wed 18 Jan 2017 05:09:16 PM CST


import struct
import time

f = open('/dev/gpio', 'wb')

while True:
    c = struct.pack('I', 0x80008000)
    f.write(c)
    f.flush()
    time.sleep(1)
    c = struct.pack('I', 0x00008000)
    f.write(c)
    f.flush()
    c = struct.pack('I', 0x80004000)
    f.write(c)
    f.flush()
    time.sleep(1)
    c = struct.pack('I', 0x00004000)
    f.write(c)
    f.flush()
