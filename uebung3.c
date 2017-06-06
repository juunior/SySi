/**
 * KLeines Programm um Metadaten aus Bilddatei zu lesen
 * 
 * @author K. Schultz, C. Wolf
*/

#include <stdio.h>
#include <string.h>
//fuer error
#include <stdlib.h>
//fuer stat
#include <sys/stat.h>
#include <sys/types.h>
//fuer open
#include <fcntl.h>
//fuer read
#include <unistd.h>

/**
 * Main Funktion
 *
 * @param argc	Anzahl der Elemente
 * @param argv	Uebergebene Elemente
*/
int main (int argc, char *argv[]) {
	//Variablen initialisieren
	struct stat st;
	int file = 0;
	char buffer[16] = {0};

	// offset off_t?
	long offset = 0X6;
	long start = 0;
	long ende = 22;

	if (argc < 2 ) {
		printf("Usage: %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (stat(argv[1], &st) == -1) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	
	for (int i = 1; i < argc; i++) {
		
		if ((file = open(argv[i], O_RDONLY)) < -1) {
			exit(EXIT_FAILURE);
		}

		lseek(file, offset, start);

		read(file,buffer,16);
		printf("%s\n", buffer);

		close(file);
	}

	exit(EXIT_SUCCESS);
}

