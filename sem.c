#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define LOCK       -1
#define UNLOCK      1
#define PERM 0666      // Zugriffsrechte
#define KEY  123458L
#define N_DATA 2000000 //Array Size
#define N_SHARED 2000 //share Memory Size

static struct sembuf semaphore;
static int semid;

static int init_semaphore(void) {
    // Testen, ob das Semaphor bereits existiert
    semid = semget(KEY, 0, IPC_PRIVATE);
    if (semid < 0) {
        // ... existiert noch nicht, also anlegen
        // Alle Zugriffsrechte setzten
        umask(0);
        semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | PERM);
        if (semid < 0) {
            perror("Fehler beim Anlegen des Semaphors ...\n");
            return -1;
        }
        printf("(angelegt) Semaphor-ID : %d\n", semid);
        // Semaphor mit 1 initialisieren
        if (semctl(semid, 0, SETVAL, (int) 1) == -1)
            return -1;
    }
    return 1;
}

static int semaphore_operation(int op) {
    semaphore.sem_op = op;
    semaphore.sem_flg = SEM_UNDO;
    if (semop(semid, &semaphore, 1) == -1) {
        perror(" semop ");
        exit(EXIT_FAILURE);
    }
    return 1;
}

int main(void) {
    int res;
    res = init_semaphore();
    if (res < 0)
        exit(EXIT_FAILURE);
    printf("Vor dem kritischen Codeausschnitt ...\n");
    semaphore_operation(LOCK);
    // Kritischer Codeausschnitt
    printf("PID %d verwendet Semaphor %d\n",
           getpid(), semid);
    printf("Im kritischen Codeabschnitt ...\n");
    sleep(10);
    semaphore_operation(UNLOCK);
    printf("Nach dem kritischen Codeausschnitt ...\n");
    //semctl (semid, 0, IPC_RMID, 0);
    exit(EXIT_SUCCESS);
}
