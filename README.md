# Thinsat Satellite
Code we are using for Rocksat Satellite

This Satellite will collect light data as well as attempt to shift it's direction using an onboard motor.

Light data is collected via 2 sensors, an Adafruit_VEML6070 UV sensor and a AS726X Visible light sensor.
An Adafruit_LSM9DS0 gyro is onboard to measure the impact caused by a generic motor

This satellite will be running for a maximum of 5 mins in upper earth orbit

As it collects data the serial output will be radioed back to mission control on earth

The raw serial data will be returned for anaylsis via a .txt file

Using the 2 parsing programs (one for the gyro data and one for the light data)
We will parse this file into 2 human readable .csv files.
