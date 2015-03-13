/*
 * This is the first 12c program written to communicate
 * with an ATMega chip on a breadboard. 
 * The program should have the ATMega light an LED
 * and also allow the ATMega to return its internal temp in deg C
 */


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

// ATMega board addresses
#define ADDRESS 0x04
#define ARDUINO2 0x05

// The I2C bus for V2 pi (V1 pi models use i2c-0)
static const char *devName = "/dev/i2c-1";

int main(int argc, char **argv)
{
	if (argc==1){
		printf("Supply one or more commands to send to the ATMega\n");
		exit(1);
	}
	
	printf("I2C: Connecting\n");
	int file;
	
	if((file = open(devName, O_RDWR)) < 0){
		fprintf(stderr, "I2C: Failed to access %d\n", devName);
		exit(1);
	}
	
	printf("I2C: aquiring bus to 0x%x\n");
	
	if (ioctl(file, I2C_SLAVE, ADDRESS) < 0){
		fprintf(stderr, "I2C: Failed to aquire bus access/talk to slave 0x%x\n", ADDRESS);
		exit(1);
	}
	
	int arg;
	
	for (arg = 1; arg < argc; arg++) {
		int val;
		unsigned char cmd[16];
		
		if (0 == sscanf(argv[arg], "%d", &val)){
			fprintf(stderr, "Invalid parameter %d \"%s\"\n", arg, argv[arg]);
			exit(1);
		}
		
		printf("Sending %d\n", val);
		
		cmd[0] = val;
		
		// since we are not talking directly to hardware 
		// but instead a microcontroller, we must wait a bit
		// so it may respond.
		// Depending on workload, 10ms is often enough.
		
		if (write(file, cmd, 1) == 1) {
			usleep(10000);
			
			char buf[1];
			if(read(file, buf, 1) == 1){
				int temp = (int) buf[0];
				printf("Received %d\n", temp);
			}	
		}		//end for loop
		
		// Now we must wait again or risk crashing ATMega from too many req
		usleep(10000);
	}

	if (temp > 20){
		close(file);
		printf("I2C: Reconnecting for Phase 2\n");
		if((file = open(devName, O_RDWR)) < 0){
			fprintf(stderr, "I2C: Failed to access %d\n", devName);
			exit(1);
		}
		printf ("I2C: Aquiring bus to 0x%x\n");
		if (ioctl(file, I@C_SLAVE, ARDUINO2) < 0){
			fprintf(stderr, "I2C: Failed to establish communications with slave at 0x%x\n", ARDUINO2);
			exit(1);
		}
		cmd[0] = val + 1;
		if (write(file, cmd, 1) == 1) {
			usleep(10000);
		}
	}

	close(file);
	
	return 0;
}

