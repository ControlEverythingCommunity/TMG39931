// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// TMG39931
// This code is designed to work with the TMG39931_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Color?sku=TMG39931_I2CS#tabs-0-product_tabset-2

#include <Wire.h>

// TMG39931 I2C address is 0x39(57)
#define Addr 0x39
  
void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select Enable register
  Wire.write(0x80);
  // Power ON, ALS enable, Proximity enable, Wait enable
  Wire.write(0x0F);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select ADC integration time register
  Wire.write(0x81);
  // ATIME : 2.78ms, maximum count = 1025
  Wire.write(0xFF);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select Wait time register
  Wire.write(0x83);
  // WTIME : 2.78ms
  Wire.write(0xFF);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x8F);
  // AGAIN is 1x
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[9];
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(148);
  // Stop I2C transmission
  Wire.endTransmission();
  
  // Request 9 bytes of data
  Wire.requestFrom(Addr, 9);
   
  // Read the 9 bytes of data
  // cData channel LSB, cData channel MSB, Red channel LSB, Red channel MSB
  // Green channel LSB, Green channel MSB, Blue channel LSB, Blue channel MSB, proximity
  if(Wire.available() == 9) 
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
    data[6] = Wire.read();
    data[7] = Wire.read();
    data[8] = Wire.read();
   }
   
  // Convert the data
  float cData = data[1] * 256.0 + data[0];
  float red = data[3] * 256.0 + data[2];
  float green = data[5] * 256.0 + data[4];
  float blue = data[7] * 256.0 + data[6];
  
  // Output data to serial monitor       
  Serial.print("Green Color Luminance : ");
  Serial.println(green);
  Serial.print("Red Color Luminance : ");
  Serial.println(red)  ;
  Serial.print("Blue Color Luminance : ");
  Serial.println(blue) ;
  Serial.print("InfraRed Luminance : ");
  Serial.println(cData) ;
  Serial.print("Proximity of the device : ");
  Serial.println(data[8]);
  delay(500);
}

