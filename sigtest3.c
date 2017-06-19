//Autor: Daniel Rohe, Merlin Geuskens

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>


volatile int SIGNO = 0;

int ackermann(int n, int m) {
    if (n == 0) {
        return m + 1;
    } else if (m == 0) {
        return ackermann(n - 1, 1);
    } else {
        return ackermann(n - 1, ackermann(n, m - 1));
    }

}

static void sighandler(int signo) {
    printf("Signal empfangen: Nummer %d\n", signo);
    SIGNO = signo;
    if (SIGNO == SIGALRM) {
        printf("Alarm wurde ausgeloest\n");
        return;
    } else if (SIGNO == SIGXCPU) {
        printf("CPU unter Last!\n");
        return;
    } else if (SIGNO == SIGWINCH) {
        printf("Fenstergroesse hat sich geÃ¤ndert!\n");
        return;
    }
    //else
    exit(EXIT_FAILURE);
}

int main(void) {
    struct sigaction sigact;
    sigset_t sigmask;
    sigfillset(&sigmask);

    sigact.sa_handler = sighandler;
    sigact.sa_mask = sigmask;
    sigact.sa_flags = 0;

    //Sigkill sowie sigstop koennen nicht behandelt werden!
    for (int i = 1; i <= 31; i++) {
        if (i != 9 && i != 17) {
            if (sigaction(i, &sigact, NULL) == -1) {
                perror("Error Signalhandler");
                return 0;
            }
        }
    }
    puts("Signalhandler ist bereit!\n");
    //alarmroutine
    alarm(5);
    sleep(10);
    //anpassen der limits fuer die CPU-Nutzung des Prozesses
    struct rlimit limit;
    limit.rlim_cur = 1;
    limit.rlim_max = 200;
    setrlimit(RLIMIT_CPU, &limit);

    //raise(SIGFPE); // division by 0 werfen
    printf("Nach Alarm in main\n");
    //Ackermannfunktion aufrufen, Werte empirisch ermittelt
    ackermann(3, 12);
    printf("Ackermann beendet\n");


    //3tes Signal: FenstergÃroesse Ã¤ndern!

    sleep(60);  //Dauer = 60 Sekunden
    return SIGNO;
}
