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
#include <bits/sigset.h>
#include <memory.h>

volatile int SigNo;

//Signalhandler
static void sigfunc(int sig) {
    SigNo = sig;
//    printf("%i\n", SigNo);
}

int main(void) {
    SigNo = 0;

    struct sigaction new_action, old_action;

    memset(&new_action, '\0', sizeof(new_action));

    new_action.sa_handler = &sigfunc;


    for (int i = 1; i <= 34; i++) {
        sigaction(i, NULL, &old_action);
        if (old_action.sa_handler != SIG_IGN) {
            sigaction(i, &new_action, NULL);
        }
    }

    sleep(60);

    if (SigNo == 0) {
        return 0;
    } else {
        return SigNo;
    }
}

