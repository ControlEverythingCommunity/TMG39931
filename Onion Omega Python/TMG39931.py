# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# TMG39931
# This code is designed to work with the TMG39931_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Color?sku=TMG39931_I2CS#tabs-0-product_tabset-2

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# TMG39931 address, 0x39(57)
# Select Enable register, 0x80(128)
#		0x0F(15)	Power ON, ALS enable, Proximity enable, Wait disable
i2c.writeByte(0x39, 0x80, 0x0F)
# TMG39931 address, 0x39(57)
# Select ADC integration time register, 0x81(129)
#		0x00(00)	ATIME : 712ms, Max count = 65535 cycles
i2c.writeByte(0x39, 0x81, 0x00)
# TMG39931 address, 0x39(57)
# Select Wait time register, 0x83(131)
#		0xFF(255)	WTIME : 2.78ms
i2c.writeByte(0x39, 0x83, 0xFF)
# TMG39931 address, 0x39(57)
# Select Control register, 0x8F(143)
#		0x00(00)	AGAIN is 1x
i2c.writeByte(0x39, 0x8F, 0x00)

time.sleep(0.8)

# TMG39931 address, 0x39(57)
# Read data back from 0x94(148), 9 bytes
# cData LSB, cData MSB, red LSB, red MSB, green LSB, green MSB, blue LSB, blue MSB, proximity
data = i2c.readBytes(0x39, 0x94, 9)

# Convert the data
cData = data[1] * 256.0 + data[0]
red = data[3] * 256.0 + data[2]
green = data[5] * 256.0 + data[4]
blue = data[7] * 256.0 + data[6]
proximity = data[8]

# Output data to screen
print "InfraRed luminance : %.2f lux" %cData
print "Red Color luminance : %.2f lux" %red
print "Green Color luminance : %.2f lux" %green
print "Blue Color luminance : %.2f lux" %blue
print "Proximity of the device : %d " %proximity
