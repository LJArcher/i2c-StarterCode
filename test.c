
// Two ATMega communication over i2c, c test code for the Raspberry pi.
//
// Reads the internal temperature reading of the ATMega1 
// and then prints to the screen.
// If the temperature reading is over 20 degree Celsius - 
// ATMega2 chip is called to turn on and off it's light.
// By James Henderson 2012.

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	printf("**** Puppet Master test program **** \n");
	int fd1;														// File1 description
	int fd2;													// File2 description
	char *fileName = "/dev/i2c-1";								// Name of the port we will be using
	int  address1 = 0x04;
	int  address2 = 0x05;										// Address of arduino1
	unsigned char buf1[10];										// Buffer for data being read/ written on the i2c bus
	unsigned char buf2[10];

	if ((fd1 = open(fileName, O_RDWR)) < 0) {					// Open port for reading and writing
		printf("Failed to open i2c port\n");
		exit(1);
	}
	else {
		printf("Opened I2C port and defined fd1... \n");
	}
		if ((fd2 = open(fileName, O_RDWR)) < 0) {					// Open port for reading and writing
		printf("Failed to open i2c port\n");
		exit(1);
	}
	else {
		printf("Opened I2C port and defined fd2... \n");
	}
	
	if (ioctl(fd1, I2C_SLAVE, address1) < 0) {					// Set the port options and set the address of the device we wish to speak to
		printf("Unable to get bus access to talk to ATMega 1\n");
		exit(1);
	}
	else {
		printf("Communications established with ATMega1... \n");
	}
	if (ioctl(fd2, I2C_SLAVE, address2) < 0) {
		printf("Unable to get bus access to talk to ATMega 2 \n");
	}
	else {
		printf("Communications established with ATMega 2... \n");
	}
	
	buf1[0] = 2;			// buf1[0] is the command we send to ATMega 1
	
	if ((write(fd1, buf1, 1)) != 1) {								// Send register to read from
		printf("Error writing to i2c ATMega 1\n");
		exit(1);
	}
	else {
		printf("Sending command to ATMega 1: %u \n", buf1[0]);
	}
	
	if (read(fd1, buf1, 10) != 10) {								// Read back data into buf[]
		printf("Unable to read from ATMega 1\n");
		exit(1);
	}
	else {
		printf("Temperature reading: %u \n", buf1[0]);
	}
	
	if (buf1[0] > 20) {
		printf("The temperature is over 20 deg Celsius on ATMega 1!! (yikes) \n");
		buf1[0] = 3;
		printf("I will turn on the light on ATMega 2, for 2 seconds! \n");
		write(fd2, buf1, 1);
		sleep(2);
		printf("I will turn off the light now. Good night! \n");
		write(fd2, buf1, 1);
	}
	return 0;
}

