/*
 * sigtest.c
 *
 *  Created on: 19.06.2017
 *      Author: wolf
 */


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int SigNo;

//Signalhandler
void sigfunc(int sig) {
	SigNo = sig;
}

int main (void) {
	SigNo = 0;
	printf("PID: %d\n", getpid());

	for (int i = 1; i < 33; i++){
		signal(i, sigfunc);
	}
	sleep(60);

	if (SigNo == 0) return 0;
		else return SigNo;
}

