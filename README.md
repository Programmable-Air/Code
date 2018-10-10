# Code

Arduino library for Programmable-Air

## Getting started:

### Powering the arduino

The Arduino Nano gets power through the 12V power plug supplied with Programmable-Air. Not from the USB cable. So, it's best to connect +12V power and then connect the USB cord to program the microcontroller.

### Installing the library

Follow the instructions for manual installation of an Arduino library as posted on the [Arduino blog here](https://www.arduino.cc/en/Guide/Libraries#toc5). If you do not have Adadfruit Neopixel library already installed, you will need to install it as well. [Instructions](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation#install-adafruit-neopixel-via-library-manager-13-2).

### Possible issues with drivers for CH340

The Arduino Nano compatible clones used in Programmable-Air use the CH340 USB-Serial chip. Some operating systems do not install the drivers for this chip on their own. If Arduino is not able to recognise the microcontroller, try installing the drivers. [Instructions](https://sparks.gogo.co.nz/ch340.html)
