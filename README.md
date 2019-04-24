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
![alt text](https://i.imgur.com/l7Na4zt.png "Procesor selection")
* Select the corresponding Port (if no new port shows up you’ll have to download and install the CH340 drivers- [Mac](http://www.wch.cn/downloads/CH341SER_MAC_ZIP.html) [Windows](https://sparks.gogo.co.nz/ch340.html) [Linux](http://www.wch.cn/downloads/CH341SER_LINUX_ZIP.html) ) The link looks sketchy and in Chinese, but it is the manufacturer’s website with the most updated version of the driver. Refrain from downloading drivers from any other source!

That's it! Try uploading the pressureSensor example and launch the Serial plotter to see the pressure plot. Blow into the output tube, or suck the air out to see the change in pressure.

### Description of functions:

`initializePins()`

Initializes the pins as INPUT or OUTPUT and starts the Serial port at 9600 baud. If you want to use pins to attach external hardware, set their pinMode after calling this.
* Does not return anything.


`blow(int i = 0);`

Used to blow air into the output tube. Engages valve #2 and disengages valve #1 and #3.
* Does not return anything.
* Accepts integer value of the slave board. Acceptable values 1, 2, or 3. Defaults to 1(the slave board below the master board).

`vent(int i = 0);`

Used to vent air from output tube to the atmosphere. Engages valve #1 and disengages valve #2 and #3.
* Does not return anything.
* Accepts integer value of the slave board. Acceptable values 1, 2, or 3. Defaults to 1(the slave board below the master board).


`ventQuick(int i = 0);`

Used to release air quickly out of the output tube. Engages valve #1, and #3 and disengages valve #1.
* Does not return anything.
* Accepts integer value of the slave board. Acceptable values 1, 2, or 3. Defaults to 1(the slave board below the master board).

`suck(int i = 0);`

Used to suck air out of the output tube. Engages valve #3 and disengages valve #1 and #2.
* Does not return anything.
* Accepts integer value of the slave board. Acceptable values 1, 2, or 3. Defaults to 1(the slave board below the master board).

`readBtn(int i);`

Returns 1 if the button is pressed, 0 if not.

* Return type : int
* Accepts button number or color. RED is button #1, BLUE is button #2


`readPressure(int num = 0, int times = 1);`

Returns the pressure value. The value is ~508 for atmospheric pressure. Greater for more pressure and lesser for less pressure.
* Return type : int
* Accepts up to two integer parameters.
	* num - integer value of the slave board. Acceptable values 1, 2, or 3. Defaults to 1(the slave board below the master board).
	* times - the number of times you want the reading to be taken and averaged. Acceptable value >1. Defaults to 1.

`setAllValves(int position);`

Set all of the valves to a the position provided. (All the valves on all the slave boards)
* Does not return anything.
* Accepts int 0 or 1(OPEN/OPENED/ENGAGE/ENGAGED or CLOSE/CLOSED/DISENGAGE/DISENGAGED)

`setValve(int number, int position);`

Sets valve number provided to position provided
* Does not return anything.
* Accepts valve number and position
	* number - int 1 to 9 for valve number.  
	* position - Accepts int 0 or 1(OPEN/OPENED/ENGAGE/ENGAGED or CLOSE/CLOSED/DISENGAGE/DISENGAGED)

`closeAllValves();`

Closes(dis-engages) all valves on all slave boards.
* Does not return anything.

`switchOnPump(int num,  int percentagePower = 100);`

Switches on pump motor # num to PWM percentage percentagePower.
* Does not return anything.
* Accepts two parameters
	* num - int motor number 1 or 2
	* percentagePower - int 0 to 100. Note that for value <30 the motor might not turn on. Defaults to 100% PWM.

`switchOffPump(int num);`

Switches off motor number num

* Does not return anything.
* num - int 1 or 2

`switchOnPumps(int percentagePower = 100);`

Switches on both motors to PWM percentage percentagePower

* Does not return anything.
* percentagePower - int 0 to 100. Note that for value <30 the motor might not turn on. Defaults to 100% PWM.

`switchOffPumps();`

Switches off both motors

* Does not return anything.
* Does not accept any parameter.

`switchOnLoad(int percentagePower = 100);`

Switches on load to PWM percentagePower. Note that the load pin gets connected to ground when switched on. So, connect the external device between power and load.

* Does not return anything.
* percentagePower - int 0 to 100. Note that for value <30 the motor might not turn on. Defaults to 100% PWM.

`switchOffLoad();`

Switches off load.

* Does not return anything.
* Does not accept any parameter.
