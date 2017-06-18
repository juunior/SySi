#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <stdbool.h>

#define LOCK       -1
#define UNLOCK      1
#define PERM 0666      // Zugriffsrechte
#define KEYSEM 133742L //Semaphorenkey
#define KEYMEM 111337L //Shared Memory Key
#define N_DATA 20 //Array Size
#define N_SHARED 2  //share Memory Size

static struct sembuf semaphore;
static int semid;

//Prototypes
static int init_semaphore(void);

static int semaphore_operation(short op);

static void fuelleArray(int *array);

int main(void) {
    int data[N_DATA];
    int semid;
    int shmid;
    int chpid;
    int *shmdata;
    int writeCount = 0;
    int readOffset = 0;

    semid = init_semaphore();
    printf("%i",semid);
    if (semid < 0) {
        exit(EXIT_FAILURE);
    }

    fuelleArray(data);
    shmid = shmget(KEYMEM, N_SHARED, IPC_CREAT);
    if (shmid == -1) {
        perror("Fehler beim Anlegen von Shared Memory:");
        exit(EXIT_FAILURE);
    }

    semaphore_operation(LOCK);  // Kritischer Codeausschnitt

    if ((chpid = fork()) < 0) {
        perror("Failure:");
        exit(EXIT_FAILURE);
    } else if (chpid == 0) {
        int childData[N_DATA];
        int readCount = 0;
        int *shmchdata;
        int writeOffset = 0;
        while (true) {
            if (semctl(semid, 0, GETVAL, 0) == 1
                    ) {
                shmchdata = shmat(shmid, NULL, 0);
                if (shmchdata == (int *) -1) {
                    printf("Fehler bei shmat(): shmid %d\n", shmid);
                }
                shmchdata += N_DATA;
                writeOffset += N_DATA;
                for (int i = 0; i < N_DATA; i++) {
                    memcpy(&childData[writeOffset], shmchdata, N_DATA);
                }
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
        if (semctl(semid, 0, GETVAL, 0) == -1) {
            shmdata = shmat(shmid, NULL, 0);
            if (shmdata == (int *) -1) {
                printf("Fehler bei shmat(): shmid %d\n", shmid);
            }
            shmdata += N_DATA;
            readOffset += N_DATA;
            for (int i = 0; i < N_DATA; i++) {
                memcpy(&shmdata, &data[readOffset], N_DATA);
            }

            writeCount++;
            semaphore_operation(UNLOCK);
            printf("stateChange Parent");
        }

        if (writeCount == (N_DATA / N_SHARED)) {
            break;
        }

    }

    semctl(semid, 0, IPC_RMID, 0);
    exit(EXIT_SUCCESS);
}

static void fuelleArray(int *array) {
    for (int i = 0; i < N_DATA; i++) {
        array[i] = rand();
    }
}

static int init_semaphore(void) {
    // Testen, ob das Semaphor bereits existiert
    semid = semget(KEYSEM, 0, IPC_PRIVATE);
    if (semid < 0) {
        // ... existiert noch nicht, also anlegen
        // Alle Zugriffsrechte setzten
        umask(0);
        semid = semget(KEYSEM, 1, IPC_CREAT | IPC_EXCL | PERM);
        if (semid < 0) {
            perror("Fehler beim Anlegen des Semaphors ...\n");
            return -1;
        }
        printf("(angelegt) Semaphor-ID : %d\n", semid);
        // Semaphor mit 1 initialisieren
        if (semctl(semid, 0, SETVAL, (int) 1) == -1) {
            return -1;
        }
    }
    return semid;
}

static int semaphore_operation(short op) {
    semaphore.sem_op = op;
    semaphore.sem_flg = SEM_UNDO;
    if (semop(semid, &semaphore, 1) == -1) {
        perror(" semop ");
        exit(EXIT_FAILURE);
    }
    return 1;
}


