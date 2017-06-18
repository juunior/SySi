#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>

#define UNLOCK 1
#define LOCK -1
#define PERM 0777      // Zugriffsrechte
#define KEYSEM 133742L //Semaphorenkey
#define KEYMEM 111337L //Shared Memory Key
#define N_DATA 20 //Array Size
#define N_SHARED 2  //share Memory Size

//Prototypes
static int init_semaphore(void);

static int semaphore_operation(short op);

static void fuelleArray(int *array);

static void child_status(int status);


static struct sembuf semaphore;
static int semaphorenID;

int main(void) {
    int data[N_DATA];
    int shmid = 0;
    int chpid = 0;
    int *shmdata;
    int writeCount = 0;
    int readOffset = 0;
    int status;

    init_semaphore();
    printf("%i",semaphorenID);
    printf("%i",semaphorenID);
    if (semaphorenID < 0) {
        exit(EXIT_FAILURE);
    }

    fuelleArray(data);
    shmid = shmget(KEYMEM, N_SHARED, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("Fehler beim Anlegen von Shared Memory:");
        exit(EXIT_FAILURE);
    }

    semaphore_operation(0);  // Kritischer Codeausschnitt

    if ((chpid = fork()) < 0) {
        perror("Failure:");
        exit(EXIT_FAILURE);
    } else if (chpid == 0) {
        int childData[N_DATA];
        int readCount = 0;
        int *shmchdata;
        int writeOffset = 0;
        while (true) {
            if (semctl(semaphorenID, 0, GETVAL, 0) == UNLOCK) {
                shmchdata = shmat(shmid, NULL, 0);
                if (shmchdata == (int *) -1) {
                    printf("Fehler bei shmat(): shmid %d\n", shmid);
                }
                shmchdata += N_DATA;
                writeOffset += N_DATA;
                for (int i = 0; i < N_DATA; i++) {
                    memcpy(&childData[writeOffset], shmchdata, N_DATA);
                }

                shmdt(shmchdata);
                readCount++;
                semaphore_operation(LOCK);
                printf("stateChange Child");

            }

            if (readCount == (N_DATA / N_SHARED)) {
                break;
            }
        }
        exit(EXIT_SUCCESS);
    }
    while (true) {
        printf("%i\n",semctl(semaphorenID, 0, GETVAL, 0));
        if (semctl(semaphorenID, 0, GETVAL, 0) == LOCK) {
            shmdata = shmat(shmid, NULL, 0);
            if (shmdata == (int *) -1) {
                perror("Fehler bei shmat():");
            }
            shmdata += N_DATA;
            readOffset += N_DATA;
            for (int i = 0; i < N_DATA; i++) {
                memcpy(&shmdata, &data[readOffset], N_DATA);
            }

            shmdt(shmdata);
            writeCount++;
            semaphore_operation(UNLOCK);
            printf("stateChange Parent\n");
        }

        if (writeCount == (N_DATA / N_SHARED)) {
            break;
        }

    }
    if (wait (&status) != chpid) {
        perror("wait()");
        return EXIT_FAILURE;
    }
    child_status (status);

    semctl(semaphorenID, 0, IPC_RMID, 0);
    exit(EXIT_SUCCESS);
}

static void fuelleArray(int *array) {
    for (int i = 0; i < N_DATA; i++) {
        array[i] = rand();
    }
}

static int init_semaphore(void) {
    // Testen, ob das Semaphor bereits existiert
    semaphorenID = semget(KEYSEM, 0, IPC_PRIVATE);
    if (semaphorenID < 0) {
        // ... existiert noch nicht, also anlegen
        // Alle Zugriffsrechte setzten
        umask(0);
        semaphorenID = semget(KEYSEM, 1, IPC_CREAT | IPC_EXCL | PERM);
        if (semaphorenID < 0) {
            perror("Fehler beim Anlegen des Semaphors ...\n");
            return -1;
        }
        printf("(angelegt) Semaphor-ID : %d\n", semaphorenID);
        // Semaphor mit 1 initialisieren
        if (semctl(semaphorenID, 0, SETVAL, (int) 1) == -1) {
            return -1;
        }
    }
    return 1;
}

static int semaphore_operation(short op) {
    semaphore.sem_op = op;
    semaphore.sem_flg = SEM_UNDO;
    if (semop(semaphorenID, &semaphore, 1) == -1) {
        perror(" semop ");
        exit(EXIT_FAILURE);
    }
    return 1;
}

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
        /* I.d.R. wird dies SIGSTOP sein, aber es gibt */
        /* ja auch noch das ptrace()-Interface.        */
    }
}

