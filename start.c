#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>


static void child_status(int status) {
    if (WIFEXITED (status)) {
        printf("Kind normal beendet mit Rückgabewert %d\n",
               WEXITSTATUS(status));
    } else if (WIFSIGNALED (status)) {
        printf("Kind mit Signalnummer %d beendet\n",
               WTERMSIG(status));
    }
#ifdef __FreeBSD__
        else if (WCOREDUMP(status)) {
               printf("Kind hat eine Core-Datei angelegt");
        }

#endif
    else if (WIFSTOPPED (status)) {
        printf("Kind wurde angehalten mit Signalnummer %d\n",
               WSTOPSIG(status));
    }
}

int main(int argc, char **argv) {
    int pid;
    int status;

    if ((pid = fork()) < 0) {
        perror("Failure:");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        pid = getpid();

        printf("PID of child for %s: %i\n\n", argv[1], pid);
        execvp(argv[1], &argv[1]);

    }

    if (wait (&status) != pid) {
        perror("wait()");
        return EXIT_FAILURE;
    }

    /* Status vom Kind auswerten */
    printf("\n");
    child_status (status);


        return 0;
    }
