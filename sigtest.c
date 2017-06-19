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

//volatile int *a;

//Signalhandler??
void sigfunc(int sig) {
	/* wenn SIGABRT dann gebe beenden aus und breche ab*/
	if(sig == SIGABRT){
		printf("Beenden!\n");
	}
}

int main (void) {
	//irrelevant
	int a = getpid();
	printf("PID: %d\n", a);

	/* signalhandler wird aufgerufen
	 * d.h. die Funktion signal ruft bei einem abbruch die sigfunc auf
	 * danach wird das Programm beendet
	 */

	signal(SIGABRT, sigfunc);
	abort();
	return EXIT_SUCCESS;

}
