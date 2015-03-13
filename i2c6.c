
// TPA81 example c code for the Raspberry pi.
//
// Reads the software revision of the TPA81 and all temperature data
// and then prints to the screen.
//
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
	printf("**** Puppet Master test program ****,\n");
	int fd;														// File descrition
	char *fileName = "/dev/i2c-1";								// Name of the port we will be using
	int  address1 = 0x04;
	int address2 = 0x05;										// Address of arduino1
	unsigned char buf1[10];										// Buffer for data being read/ written on the i2c bus
	unsigned char buf2[10];

	if ((fd = open(fileName, O_RDWR)) < 0) {					// Open port for reading and writing
		printf("Failed to open i2c port\n");
		exit(1);
	}
	else {
		printf("Opened I2C port \n");
	}
	
	if (ioctl(fd, I2C_SLAVE, address1) < 0) {					// Set the port options and set the address of the device we wish to speak to
		printf("Unable to get bus access to talk to slave\n");
		exit(1);
	}
	else {
		printf("Communications established with ATMega1 \n");
	}

	
	buf1[0] = 2;				// buf[0]  is the element we send to slave
	
	if ((write(fd, buf1, 1)) != 1) {								// Send register to read from
		printf("Error writing to i2c slave\n");
		exit(1);
	}
	else {
		printf("Sending command: %u \n", buf1[0]);
	}
	
	if (read(fd, buf1, 10) != 10) {								// Read back data into buf[]
		printf("Unable to read from slave\n");
		exit(1);
	}
	else {
		printf("Temperature reading: %u \n", buf1[0]);
	}
	
	if (buf1[0] > 20) {
		buf1[0] = 1;
		write(fd, buf1, 1);
		sleep(2);
		write(fd, buf1, 1);
	}
	return 0;
}

