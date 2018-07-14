#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>
#include "Adafruit_VEML6070.h"
#include "AS726X.h"

int counter = 0;

AS726X sensor; //Creates the AS726X sensor for visable light senseing
Adafruit_VEML6070 uv = Adafruit_VEML6070(); //Create the VEML6070 for UV Intensity detection



double lastGyroReading = 0;

const byte GAIN = 1; //Set gain for AS726X, 1 is 3.7x

const byte MEASUREMENT_MODE = 2; //Declare the measurement mode for AS726X



Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(1000);  //Assigns an identifer for the sensor. Use I2C, ID #1000


/*

   Can we remove these #define statements if you arn't going to use them?
   it appears you have commented all lines that reference away

*/

#define LSM9DS0_XM_CS 10
#define LSM9DS0_GYRO_CS 9
#define LSM9DS0_SCLK 13
#define LSM9DS0_MISO 12
#define LSM9DS0_MOSI 11
//Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(LSM9DS0_SCLK, LSM9DS0_MISO, LSM9DS0_MOSI, LSM9DS0_XM_CS, LSM9DS0_GYRO_CS, 1000);
//Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(LSM9DS0_XM_CS, LSM9DS0_GYRO_CS, 1000);



void displaySensorDetails(void)
{
  sensor_t accel, mag, gyro, temp;

  lsm.getSensor(&accel, &mag, &gyro, &temp);
}

void configureSensor(void)
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);

  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);
}

void setup(void)
{
  sensor.begin(Wire, GAIN, MEASUREMENT_MODE); // Initializes the sensor with non default values

  lsm.begin();

  pinMode(6, OUTPUT);

  displaySensorDetails(); // Displays details about Gyro sensor **CAN WE REMOVE THIS?**

  configureSensor(); // Configures the Gyro Sensor to specific settings

  uv.begin(VEML6070_4_T); // Begins UV reading at a 4T rate
}


void loop(void)
{
  spinMotor(millis());
  lightReadings(); //Print Light Readings
  gyroReadings();  //Print Gyro Readings

}



void spinMotor(long el) {
  if (el < 10000 && el > 0) {
    if (switchStep == 0) {
      Serial.print("@1 "); Serial.println(el);
      switchStep++;
    }
  }
  else if (el >= 10000  && el < 15000) {
    if (counter == 0) {
      startMotor();
      counter = 1;
    }
    analogWrite(6,150);
    if (switchStep == 1) {
     Serial.print("@2 "); Serial.println(el);
      switchStep++;
    }
  }
  else if (el >= 15000 && el < 20000) {
    analogWrite(6,200);
    if (switchStep == 2) {
      Serial.print("@3 "); Serial.println(el);
      switchStep++;
    }
  }
  else if (el >= 20000 && el < 35000) {
    analogWrite(6,225);
    if (switchStep == 3) {
      Serial.print("@4 "); Serial.println(el);
      switchStep++;
    }
  }
  else if (el >= 35000) {
    analogWrite(6,0);
    if (switchStep == 4) {
      Serial.print("@5 "); Serial.println(el);
      switchStep++;
    }
  }
}

void startMotor() {
  analogWrite(6,255);
  delay(100);
}

void gyroReadings() {

  sensors_event_t accel, mag, gyro, temp;

  lsm.getEvent(&accel, &mag, &gyro, &temp);

  Serial.print("*"); //Tag the data for parsing

  Serial.print(millis());  Serial.print(","); //Record time since arduino turned on

  Serial.print(accel.acceleration.x); Serial.print(","); //Record Accceleration in the X Direction
  Serial.print(accel.acceleration.y); Serial.print(","); //Record Accceleration in the Y Direction
  Serial.print(accel.acceleration.z); Serial.print(","); //Record Accceleration in the Z Direction

  Serial.print(mag.magnetic.x); Serial.print(","); //Record Magnetic in the X Direction
  Serial.print(mag.magnetic.y); Serial.print(","); //Record Magnetic in the Y Direction
  Serial.print(mag.magnetic.z); Serial.print(","); //Record Magnetic in the Z Direction

  Serial.print(gyro.gyro.x); Serial.print(","); //Record Gyro in the X Direction
  Serial.print(gyro.gyro.y); Serial.print(","); //Record Gyro in the Y Direction
  Serial.print(gyro.gyro.z); Serial.print(","); //Record Gyro in the Z Direction

  Serial.println(temp.temperature); //Record Temperature
}

void lightReadings() {

  sensor.takeMeasurements(); //Take measurements from the AS726X

  Serial.print("$"); //Tag the data for parsing

  Serial.print(millis());  Serial.print(","); //Record time since arduino turned on

  Serial.print(uv.readUV()); Serial.print(","); //Record UV Intensity Reading

  Serial.print(sensor.getCalibratedViolet());  Serial.print(","); //Record Calibrated Violet
  Serial.print(sensor.getCalibratedBlue());  Serial.print(","); //Record Calibrated Blue
  Serial.print(sensor.getCalibratedGreen());  Serial.print(","); //Record Calibrated Green
  Serial.print(sensor.getCalibratedYellow());  Serial.print(","); //Record Calibrated Yellow
  Serial.print(sensor.getCalibratedOrange());  Serial.print(","); //Record Calibrated Orange
  Serial.print(sensor.getCalibratedRed());  Serial.print(","); //Record Calibrated Red

  Serial.print(sensor.getCalibratedV());  Serial.print(","); //Record Calibrated NIR V
  Serial.print(sensor.getCalibratedS());  Serial.print(","); //Record Calibrated NIR S
  Serial.print(sensor.getCalibratedT());  Serial.print(","); //Record Calibrated NIR T
  Serial.print(sensor.getCalibratedU());  Serial.print(","); //Record Calibrated NIR U
  Serial.print(sensor.getCalibratedW());  Serial.print(","); //Record Calibrated NIR W
  Serial.print(sensor.getCalibratedR());  Serial.print(","); //Record Calibrated NIR R

  Serial.println(sensor.getTemperatureF());  //Record Temperature
}

