/*
	created by : wolf	
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>


volatile int SigNo = 0;

//Cpu unter Last stellen
int cpu_time(int n, int m) {
    if (n == 0) {
        return m + 1;
    } else if (m == 0) {
        return cpu_time(n - 1, 1);
    } else {
        return cpu_time(n - 1, cpu_time(n, m - 1));
    }

}

//
static void sighandler(int signo) {
    printf("Signal empfangen: Nummer %d\n", signo);
    SigNo = signo;
    if (SigNo == SIGALRM) {
        printf("Alarm wurde ausgeloest\n");
        return;
    } else if (SigNo == SIGXCPU) {
        printf("CPU heizt auf!\n");
        return;
    } else if (SigNo == SIGWINCH) {
        printf("Fenstergroesse hat sich veraendert!\n");
        return;
    }
    exit(EXIT_FAILURE);
}

int main(void) {
    struct sigaction sigact;
    sigset_t sigmask;
    sigfillset(&sigmask);

    sigact.sa_handler = sighandler;
    sigact.sa_mask = sigmask;
    sigact.sa_flags = 0;

    //Sigkill sowie sigstop koennen nicht gefangen werden, werden vom Kernel durchgesetzt!
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
    //CPU Limit Zeit setzen
    struct rlimit limit;
    limit.rlim_cur = 1;
    limit.rlim_max = 200;
    setrlimit(RLIMIT_CPU, &limit);

    //raise(SIGFPE); // division by 0 werfen
    printf("Nach Alarm in main\n");
    //CPU-Zeit generieren, Werte empirisch ermittelt
    cpu_time(3, 9);
    printf("CPU Zeit rlimit_cur erreicht --> SIGXCPU\n");

    sleep(60);  //Dauer = 60 Sekunden
    return SigNo;
}
