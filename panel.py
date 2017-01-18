#!/usr/bin/env python
# encoding: utf-8
# File Name: panel.py
# Author: Fang Yuan (yfang@nju.edu.cn)
# Created Time: Wed 18 Jan 2017 06:45:03 PM CST

import Tkinter as tk
import gpio

buttons = []
states = []
# pin number corresponding GPIO pins. -1 means non-gpio
pinfunc = (-1, -1, 2, -1, 3, -1, 4, 14, -1, 15, 17, 18,
           27, -1, 22, 23, -1, 24, 10, -1, 9, 25, 11, 8,
           -1, 7, -1, -1, 5, -1, 6, 12, 13, -1, 19, 16,
           26, 20, -1, 21)
led = gpio.GPIO('xxxx')


def toggleLED(i):
    k = i - 1
    states[k] = 1 - states[k]
    led.setPin(pinfunc[k], states[k])

root = tk.Tk()

for i in range(1, 41, 2):
    f = tk.Frame(root)
    f.pack(side=tk.TOP, expand=tk.YES, fill=tk.X)
    f1 = tk.Frame(f)
    f2 = tk.Frame(f)
    f1.pack(side=tk.LEFT, expand=tk.YES, fill=tk.X)
    f2.pack(side=tk.RIGHT, expand=tk.YES, fill=tk.X)

    l = tk.Label(f1, text=str(i))
    l.pack(side=tk.LEFT, expand=tk.YES, fill=tk.X)
    chk = tk.Checkbutton(f1, command=(lambda i=i: toggleLED(i)))
    chk.pack(side=tk.RIGHT, fill=tk.X)

    states.append(0)
    buttons.append(chk)

    l = tk.Label(f2, text=str(i+1))
    l.pack(side=tk.RIGHT, expand=tk.YES, fill=tk.X)
    chk = tk.Checkbutton(f2, command=(lambda i=i+1: toggleLED(i)))
    chk.pack(side=tk.LEFT, fill=tk.X)

    states.append(0)
    buttons.append(chk)

for i in range(0, 40):
    if pinfunc[i] == -1:
        buttons[i]['state'] = tk.DISABLED

root.mainloop()
