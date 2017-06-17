#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main (int argc, char **argv){
    int pid;

    if((pid = fork()) < 0) {
        perror("Failure:");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) {
        printf("Child:%i\n",getpid());
        execvp(argv[1], &argv[1]);
    }
    else {
        printf("Parent:%i\n",getpid());
    }


    return 0;
}
