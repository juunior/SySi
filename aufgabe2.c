#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/param.h>

int main (int argc, char *argv[]) {
	struct stat st;

	if (argc < 2) {
		printf("Usage: %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (stat(argv[1], &st) == -1) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	
	for(int i=1; i < argc; i++){
		
		lstat(argv[i],&st);
		char type[20];
	
		if (S_ISREG(st.st_mode)){
			strcpy(type, "regular file");
		}else if (S_ISLNK(st.st_mode)){
			strcpy(type, "symbolic link");
		}else if (S_ISDIR(st.st_mode)){
			strcpy(type, "directory");
		}else if (S_ISCHR(st.st_mode)){
			strcpy(type, "character device");
		}else if (S_ISFIFO(st.st_mode)){
			strcpy(type, "FIFO (named Pipe)");
		}else if (S_ISSOCK(st.st_mode)){
			strcpy(type,"socket");
		}

		printf("File: \t\t\t %s \n", argv[i]);
		printf("Filetype\t\t %s \n", type);
		printf("UserID:\t\t\t %d \n", st.st_uid);
		printf("GroupID: \t\t %d \n", st.st_gid);
		printf("letzter Zugriff:\t %s", ctime(&st.st_atime));
		printf("letzte Inodeaenderung:\t %s", ctime(&st.st_ctime));
		printf("letzte Aenderung: \t %s", ctime(&st.st_mtime));
		
		#ifdef __FreeBSD__
		#printf("%s", ctime(&st.st_birthtime));
		#endif
	
	}
	

	exit(EXIT_SUCCESS);
}
