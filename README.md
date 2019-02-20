# Code

Arduino library for Programmable-Air

## Getting started:

As a first step you should read the [README](https://github.com/Programmable-Air/PCB/) file in the PCB section to get acquainted with the hardware. This is not necessary as such, but highly recommended.

### Software
* Download and install Arduino 1.8.7
* Download the Programmable-Air library at https://github.com/Programmable-Air/Code Instructions on how to install a new library in Arduino [here](https://www.arduino.cc/en/Guide/Libraries#toc4)
* Now there should be a programmable_air folder in File>examples
* If you do not have Adafruit Neopixel library already installed, you will need to install it as well. [Instructions](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation#install-adafruit-neopixel-via-library-manager-13-2).

### Hardware		
* Power up the Programmable-Air unit by connecting 12V adapter. Then connect the USB cable to your computer.

### Uploading code

* Select Tools>Board>Arduino Nano
* If you are on a new version of Arduino >=1.8.7 select Processor: AtMega328(Old bootloader)
* Select the corresponding Port (if no new port shows up you’ll have to download and install the CH340 drivers- [Mac](http://www.wch.cn/downloads/CH341SER_MAC_ZIP.html) [Windows](http://www.wch.cn/downloads/CH341SER_ZIP.html) [Linux](http://www.wch.cn/downloads/CH341SER_LINUX_ZIP.html) ) The link looks sketchy and in Chinese, but it is the manufacturer’s website with the most updated version of the driver. Refrain from downloading drivers from any other source!

That's it! Try uploading the pressureSensor example and launch the Serial plotter to see the pressure plot. Blow into the output tube, or suck the air out to see the change in pressure.

### Description of functions:

`initializePins()`
**No return type.**
Initializes the pins as INPUT or OUTPUT and starts the Serial port. If you want to use pins to attach external hardware, set their pinMode after calling this.
