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

#define BUF_MAX 100

/**
 * Main Funktion
 *
 * @param argc	Anzahl der Elemente
 * @param argv	Uebergebene Elemente
*/
int main (int argc, char *argv[]) {
	
	//Variablen initialisieren
	//struct stat st;
	int file = 0;
	char buffer[BUF_MAX] = {0};

	if (argc < 2 ) {
		printf("Usage: %s <pathname of Image>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	for (int i = 1; i < argc; i++) {
		
		if ((file = open(argv[i], O_RDONLY)) == -1) {
			perror("Failure");
			exit(EXIT_FAILURE);
		}
			printf("Exif of %s \n",argv[i]);

			if (lseek(file, 0xB6, SEEK_SET) == -1) {
				exit(EXIT_FAILURE);
			}
	                read(file,buffer,BUF_MAX);

			
			printf("Date: \t\t%s\n", buffer);

			if (lseek(file, 0xCa, SEEK_SET) == -1) {
				exit(EXIT_FAILURE);
			}
			read(file,buffer,BUF_MAX);
			printf("Camera: \t%s\n", buffer);
		
		close(file);
	}

	exit(EXIT_SUCCESS);
}

