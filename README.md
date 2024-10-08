# Eket Growbox Controller

This project implements an Arduino-based controller for an Eket growbox, managing lighting, ventilation, and humidity for optimal plant growth conditions.

## Hardware Requirements

- Arduino Uno or similar microcontroller with 3 PWM outputs
- DHT11 humidity sensor
- Growlight of your choice (COB f5454 used here)
- Relay module (for lighting control)
- PC fans (for circulation, exhaust and cooling of the light if needed)
- 3 MOSFETs (for fan speed control, see schematic. IRFZ44N used here)
- DS1307 Real-Time Clock (RTC) module
- 12V power supply (for fans)
- Eket cabinet (IKEA)
- 3D printed parts for mounting fans (see [3D Parts](#3d-parts))

## Features

- Automated lighting control based on time of day
- Humidity-based ventilation control
- Real-time clock for accurate timing
- Adjustable fan speeds for circulation and exhaust
- Temperature and humidity monitoring via Serial.print

## Pin Configuration

- Humidity Sensor (DHT11): Pin 7
- Relay (for lights): Pin 8
- Circulation Fan: Pin 9
- Exhaust Fan: Pin 10
- Light Cooling Fan: Pin 11

## Setup

1. Connect the components to the Arduino. Build the mosfets with this [schematic](https://forum.arduino.cc/t/controlling-2-pin-12v-fans-intermittently/1126602/4).
2. Upload the provided Arduino sketch to your Arduino.
3. Adjust the time settings in the `setup()` function if necessary. If you experience PWM Noise, use the setPWMFrequency function

## Usage

Once powered on, the system will:

1. Initialize the RTC and sensors
2. Control lighting based on the time of day (on between 6:00 and 23:59)
3. Adjust fan speeds based on humidity levels
4. Display current time, temperature, and humidity readings via Serial Monitor

## Customization

You can adjust the following parameters in the code:

- Lighting schedule in the `controlLightingAndFan()` function
- Humidity thresholds and fan speeds in the `controlHumidity()` function
- PWM frequency for fans using the `setPwmFrequency()` function

## 3D Parts

Some 3D-printed parts are required if you're using CPU fans. These parts help mount the fans securely within the Eket cabinet. The 3D model files are not included in this repository.

## Carbon Filter Adapter

An adapter for coal filters is included in the design. This is only necessary if you plan to use the Eket as a drying box. Please note that this feature is still a work in progress and a custom made 3d printable model is in the making.

## Future Development

The project is still under development. Planned features include:

- Different operational modes depending on the plant growth stage:
  - Vegetation
  - Flowering
  - Drying/Curing

Each mode will have optimized settings for lighting, ventilation, and humidity control.

. 3D model for the carbon filter

## Troubleshooting

If you encounter issues:

1. Check all connections
2. Ensure the RTC is properly initialized
3. Verify that the DHT11 sensor is functioning correctly. Often times than not they are quite unprecise/ not working properly.

For more detailed troubleshooting, check the serial output for error messages.

## Contributing

This project is open for contributions. If you have suggestions or improvements, please open an issue or submit a pull request.

## License

MIT License

Copyright (c) 2024 N. Nakropin
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.