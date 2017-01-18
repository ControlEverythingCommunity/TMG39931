// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// TMG39931
// This code is designed to work with the TMG39931_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Color?sku=TMG39931_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, TMG39931 I2C address is 0x39(57)
	ioctl(file, I2C_SLAVE, 0x39);

	// Set Wait Time register(0x83)
	// Wtime = 2.78 ms,(0xFF)
	char config[2] = {0};
	config[0] = 0x83;
	config[1] = 0xFF;
	write(file, config, 2);
	// Set Atime register(0x81)
	// ATIME : 712ms, Max count = 65535 cycles
	config[0] = 0x81;
	config[1] = 0x00;
	write(file, config, 2);
	// Select enable register(0x80)
	// Power ON, ALS enable, Proximity enable, Wait enable(0x0F)
	config[0] = 0x80;
	config[1] = 0x0F;
	write(file, config, 2);
	sleep(1);

	// Read 9 Bytes of Data
	// cData lsb, cData msb, red lsb, red msb, green lsb, green msb, blue lsb, blue msb, proximity
	char reg[1] = {0x94};
	write(file, reg, 1);
	char data[9] = {0};
	if(read(file, data, 9) != 9)
	{
		printf("Erorr : Input/output Erorr \n");
	}
	else
	{
		// Convert the data
		int cData = (data[1] * 256 + data[0]);
		int red = (data[3] * 256 + data[2]);
		int green = (data[5] * 256 + data[4]); 
		int blue = (data[7] * 256 + data[6]);
		int proximity = data[8];

		// Output data to screen
		printf("InfraRed luminance : %d lux \n", cData);
		printf("Red Color luminance : %d lux \n", red);
		printf("Green Color luminance : %d lux \n", green);
		printf("Blue Color luminance : %d lux \n", blue);
		printf("Proximity of the device : %d \n", proximity);
	}
}
