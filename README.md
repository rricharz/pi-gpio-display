# pi-gpio-display

Displays the logic value of the general purpose gpio pins on the 
Raspberry Pi gpio connector.

![Alt text](screenshot.jpg?raw=true "pi-gpio-display")

**You must be user pi to install and run this program**

To install:

- Open a terminal and type:

```
  sudo apt-get install wiringpi
  cd Downloads
  git clone git://github.com/rricharz/pi-gpio-display
  cd pi-gpio-display
  chmod +x ./install
  ./install
```
- Reboot your pi

If you want to recompile the program, you need to install

```
  sudo apt-get install libgtk-3-dev
```

You can test the compilation with

```
  touch application.c
  make
```

This program does not change the mode of any of the pins, it just observes
the logic value. If you want to set any of the these pins to output, and observe
the change, you can open a console and type the following commands.
**pin#** is the green wiringPi number on the display,
**new_value** is either 1 or 0)


```
  gpio mode pin# out
  gpio write pin# new_value
```

A description of all the options of the gpio command can be found at
http://wiringpi.com/the-gpio-utility

If you want to observe the state of any of the pins as input, you can connect
the pin with a suitable resistor to ground or 3.3V,
and set the pin to input using the command

```
  gpio mode pin# in
```

**Be carefull with the gpio command** and use it only with a proper green wiringPi pin#.
Also, **be carefull hooking up anything to the gpio connector**. You might destroy
your hardware if you make a mistake. **Do not hook up any pin to 5V**.


Please open an issue in this repository or write to rricharz77@gmail.com if you have any
feedback or problem with this repository. Your input is appreciated.
