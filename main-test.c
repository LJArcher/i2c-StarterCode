
// FOUR ATMega communications over i2c, c code for the Raspberry pi.
//
// Reads the sensors from some ATMega called and conditionally responds 
// with a call to a different ATMega.
// This version of the code controls navigation
//
// Written for EGN 4952 - Engineering Design 2, Team 2: IEEE Robotics Competition
// Code written by Lisa Archer

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "i2c.h"
	

void i2cSetup() {
	printf("**** I2C Initializing!! **** \n");
	
	if ((comms1 = open(i2cPort, O_RDWR)) < 0) {			// Open port 1 for reading and writing & define comms 1
		printf("Failed to open i2c port\n");
		exit(1);
	}
	else {
		printf("Opened I2C port and defined Communication Port 1... \n");
	}
		if ((comms2 = open(i2cPort, O_RDWR)) < 0) {		// Open port 2 for reading and writing & define comms2
		printf("Failed to open i2c port\n");
		exit(1);
	}
	else {
		printf("Opened I2C port and defined Communication Port 2... \n");
	}
	if ((comms3 = open(i2cPort, O_RDWR)) < 0) {		// Open port 3 for reading and writing & define comms2
		printf("Failed to open i2c port\n");
		exit(1);
	}
	else {
		printf("Opened I2C port and defined Communication Port 3... \n");
	}
	if ((comms4 = open(i2cPort, O_RDWR)) < 0) {		// Open port 4 for reading and writing & define comms2
		printf("Failed to open i2c port\n");
		exit(1);
	}
	else {
		printf("Opened I2C port and defined Communication Port 4... \n");
	}
	
	if (ioctl(comms1, I2C_SLAVE, address1) < 0) {		// Set the port1 options and set the address of the device we wish to speak to
		printf("Unable to get bus access to talk to ATMega 1\n");
		exit(1);
	}
	else {
		printf("Communications line created for ATMega 1... \n");
	}
	if (ioctl(comms2, I2C_SLAVE, address2) < 0) {
		printf("Unable to get bus access to talk to ATMega 2 \n");
	}
	else {
		printf("Communications line created for ATMega 2... \n");
	}
	if (ioctl(comms3, I2C_SLAVE, address3) < 0) {		
		printf("Unable to get bus access to talk to ATMega 3\n");
		exit(1);
	}
	else {
		printf("Communications line created for ATMega 3... \n");
	}
	if (ioctl(comms4, I2C_SLAVE, address4) < 0) {
		printf("Unable to get bus access to talk to ATMega 4 \n");
	}
	else {
		printf("Communications line created for ATMega 4... \n");
	}
	
	printf("**** I2C Initialization Completed. **** \n\n");
	
	return;
}



void testRun() {

	
	buf1[0] = 2;			// buf1[0] is the command we send to ATMega 1
	
	if ((write(comms1, buf1, 1)) != 1) {			// Send register to read from
		printf("Error writing to i2c ATMega 1\n");
		exit(1);
	}
	else {
		printf("Sending command to ATMega 1: %u \n", buf1[0]);
	}
	
	if (read(comms1, buf1, 10) != 10) {				// Read back data into buf[]
		printf("Unable to read from ATMega 1\n");
		exit(1);
	}
	else {
		printf("Temperature reading: %u \n", buf1[0]);
	}
	
	if (buf1[0] > 20) {
		printf("The temperature is over 20 deg Celsius on ATMega 1!! (yikes) \n");
		buf2[0] = 3;
		printf("I will turn on the light on ATMega 2, and then ATMega 1 for 2 seconds! \n");
		write(comms2, buf2, 1);
		buf1[0] = 1;
		write(comms1, buf1, 1);
		sleep(2);
		printf("I will turn off both lights now. Good night! \n");
		write(comms2, buf2, 1);
		write(comms1, buf1, 1);
	}
}

int main(int argc, char **argv)
{
	printf("-------------------------------------------- \n");
	printf("**** Puppet Master Test program begins **** \n");
	printf("-------------------------------------------- \n");

	i2cSetup();
	
	testRun();
	
	return 0;
}


