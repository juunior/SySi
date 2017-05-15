#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/param.h>
#include <pwd.h>

int main (int argc, char *argv[]) {
	struct stat st;
	struct passwd *uid;

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
		uid = getpwuid(st.st_uid);
		char type[20];
		int statchmod = st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);	
	
		if(i > 1){
			printf("\n\n");
		}
			
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
		printf("Berechtigungen:\t\t %o\n", statchmod);
		printf("UserID:\t\t\t %d \n", st.st_uid);
		printf("Username:\t\t %s \n", uid->pw_name);
		printf("GroupID: \t\t %d \n", st.st_gid);
		printf("letzter Zugriff:\t %s", ctime(&st.st_atime));
		printf("letzte Inodeaenderung:\t %s", ctime(&st.st_ctime));
		printf("letzte Aenderung: \t %s", ctime(&st.st_mtime));
		
		#ifdef __FreeBSD__
		printf("Datei angelegt: \t %s", ctime(&st.st_birthtime));
		#endif
	
	}
	

	exit(EXIT_SUCCESS);
}

