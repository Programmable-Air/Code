# Code

Arduino library for Programmable-Air

## Getting started:

### Software
* Download and install Arduino 1.8.5
* Download the Programmable-Air library at https://github.com/Programmable-Air/Code
* Extract the files
* Move the programmable_air folder to Documents/Arduino/libraries
* Restart the Arduino IDE
* Now there should be a programmable_air folder in File>examples
* If you do not have Adafruit Neopixel library already installed, you will need to install it as well. [Instructions](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation#install-adafruit-neopixel-via-library-manager-13-2).

### Hardware		
* Remove the Arduino Nano from the Programmable-Air unit
* Connect the Arduino to your computer with a USB cable and make sure it DOES NOT power on. This is done to separate computer USB power from Arduino Nano +5V.
* Disconnect the Arduino from your computer and place it back on the Programmable-Air unit
* Power up the Programmable-Air unit by connecting 12V adapter. Then connect the USB cable to your computer.

### Uploading code

* Select Tools>Board>Arduino Nano
* If you are on a new version of Arduino >=1.8.7 select Processor: AtMega328(Old bootloader)
* Select the corresponding Port (if no new port shows up you’ll have to download and install the CH340 drivers- [Mac](http://www.wch.cn/downloads/CH341SER_MAC_ZIP.html) [Windows](http://www.wch.cn/downloads/CH341SER_ZIP.html) [Linux](http://www.wch.cn/downloads/CH341SER_LINUX_ZIP.html) ) The link looks sketchy and in Chinese, but it is the manufacturer’s website with the most updated version of the driver. Refrain from downloading drivers from any other source!
