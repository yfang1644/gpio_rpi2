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
pinfunc = (-1, -1, -1, -1, -1, -1, -1, -1, -1, 81,
           -1, 80, 78, 79, 76, 77, 74, 75, 72, 73, 70, 71)


for i in range(70, 82):
    gpio.GPIO(i, 'high')


def toggleLED(i):
    g = '/gpio'+str(pinfunc[i])
    f = open(gpio.GPIO_ROOT+g+'/value', 'w')
    states[i] = 1 - states[i]
    f.write(str(states[i]))

root = tk.Tk()

for i in range(0, 22, 2):    # draw pins 25 through 46
    f = tk.Frame(root)
    f.pack(side=tk.TOP, expand=tk.YES, fill=tk.X)
    f1 = tk.Frame(f)
    f2 = tk.Frame(f)
    f1.pack(side=tk.LEFT, expand=tk.YES, fill=tk.X)
    f2.pack(side=tk.RIGHT, expand=tk.YES, fill=tk.X)

    l = tk.Label(f1, text=str(i+25))
    l.pack(side=tk.LEFT, expand=tk.YES, fill=tk.X)
    chk = tk.Checkbutton(f1, command=(lambda i=i: toggleLED(i)))
    chk.pack(side=tk.RIGHT, fill=tk.X)

    states.append(0)
    buttons.append(chk)

    l = tk.Label(f2, text=str(i+26))
    l.pack(side=tk.RIGHT, expand=tk.YES, fill=tk.X)
    chk = tk.Checkbutton(f2, command=(lambda i=i+1: toggleLED(i)))
    chk.pack(side=tk.LEFT, fill=tk.X)

    states.append(0)
    buttons.append(chk)

for i in range(0, 22):
    if pinfunc[i] == -1:
        buttons[i]['state'] = tk.DISABLED

root.mainloop()
