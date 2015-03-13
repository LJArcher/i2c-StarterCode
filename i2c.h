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

static int comms;							// Master communications path
static int comms1;							// Communication path for ATMega1
static int comms2;							// Communication path for ATMega2
static int comms3;							// Communication path for ATMega3
static int comms4;							// Communication path for ATMega4

static char *i2cPort = "/dev/i2c-1";		// Name of the i2c port

static int  address1 = 0x04;				// Address of ATMega1
static int  address2 = 0x05;				// Address of ATMega2
static int  address3 = 0x06;				// Address of ATMega3
static int  address4 = 0x07;				// Address of ATMega4


unsigned char buf1[10];				// Buffer for data dedicated to ATMega1
unsigned char buf2[10];				// Buffer for data dedicated to ATMega2
unsigned char buf3[10];				// Buffer for data dedicated to ATMega3
unsigned char buf4[10];				// Buffer for data dedicated to ATMega4
