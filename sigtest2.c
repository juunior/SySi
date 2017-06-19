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
#include <string.h>

volatile int SigNo;

//Signalhandler
void sigfunc(int sig) {
	SigNo = sig;
}

int main (void) {
	SigNo = 0;
    struct sigaction act;

    memset(&act, '\0', sizeof(act));

    act.sa_sigaction = &sigfunc;
    act.sa_flags = SA_SIGINFO;

	//irrelevant
	printf("PID: %d\n", getpid());

//	for (int i = 1; i < 33; i++){
//		signal(i, sigfunc);
//	}
    if (sigaction(SIGTERM, &act, NULL) < 0) {
        perror ("sigaction");
        return 1;
    }
	sleep(60);

	if (SigNo == 0) return 0;
		else return SigNo;
}

