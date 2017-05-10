#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main (int argc, char *argv[]) {
	struct stat st;

	if (argc < 2) {
		printf("Usage: %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (stat(argv[1], &st) == -1) {
		perror("stat");
		exit(EXIT_FAILURE);
	}
	
	for(int i=1; i < argc; i++){
		
		lstat(argv[i],&st);
		
		printf("%d \n", st.st_mode);
	
	
	
	}
	

	exit(EXIT_SUCCESS);
}
