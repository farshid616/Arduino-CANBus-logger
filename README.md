# Arduino-CANBus-logger
This device will store one copy of every can packet that receive on SD card

## Setup Device
To setup this device we need:
* [Arduino UNO R3](https://www.amazon.com/Arduino-Uno-R3-Microcontroller-A000066/dp/B008GRTSV6) x1

![Arduino Uno R3](https://cdn.sparkfun.com//assets/parts/6/3/4/3/11021-04.jpg "Arduino Uno R3")

* [CAN to SPI module](https://www.amazon.com/MCP2515-Module-TJA1050-receiver-controller/dp/B01LYZ8874) x1

![CAN to SPI module](https://images-na.ssl-images-amazon.com/images/I/71uRRuiO1GL._SX425_.jpg "CAN to SPI module")

* [Arduino Data Logger Shield (SD card + RTC module)](https://www.amazon.com/Adafruit-Assembled-Logging-Shield-Arduino/dp/B00OKCRZ7A) x1

![Data Logger Shield](https://images-na.ssl-images-amazon.com/images/I/61Ih1U4xaWL._SX342_.jpg "Data Logger Shield")

First of all attach Data logger shield on you arduino. Then connect the CAN to SPI module as the picture bellow.

![Can to SPI connection](https://14core.com/wp-content/uploads/2015/12/OBDCAN-Arduino-SPI-Communication-Bus-Illustration-Diagram.jpg "Arduino Can to SPI connection")

For more information you can visit the [reference](https://www.14core.com/wiring-the-mcp2515-controller-area-network-can-bus-diagnostics/) website.

Device Picture:

![Can Data Logger](https://image.ibb.co/dkfoWo/Can_Data_Logger.jpg "Can Data Logger")

## Details


## How to run
After setup phase open Arduino ide and program the device with code. First time to adjust RTC current time, just uncomment the RTC adjust if statement on line 41-48.
```
   if (! rtc.isrunning()) {
     /*January 21, 2018 at 11:30am you would call:*/
     rtc.adjust(DateTime(2018, 1, 21, 11, 30, 00));
   }
```

## Author
Farshid Abdollahi
