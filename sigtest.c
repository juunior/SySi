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

	//irrelevant
	printf("PID: %d\n", getpid());

	/* signalhandler wird aufgerufen
	 * d.h. die Funktion signal ruft bei einem abbruch die sigfunc auf
	 * danach wird das Programm beendet
	 */
	for (int i = 1; i < 33; i++){
		signal(i, sigfunc);
	}
	sleep(60);

	if (SigNo == 0) return 0;
		else return SigNo;
/*
	printf("SigNo: %d\n", SigNo);
	return SigNo;
*/
}

