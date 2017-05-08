#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	struct stat st;

	if (argc != 2) {
		printf(stderr, "Usage: %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (stat(argv[1], &st) == -1) {
		perror("stat");
		exit(EXIT_FAILURE);
	}

	printf("File type:                ");

	switch (st.st_mode & S_IFMT) {
		case S_IFBLK:  printf("block device\n");            break;
		case S_IFCHR:  printf("character device\n");        break;
		case S_IFDIR:  printf("directory\n");               break;
		case S_IFIFO:  printf("FIFO/pipe\n");               break;
		case S_IFLNK:  printf("symlink\n");                 break;
		case S_IFREG:  printf("regular file\n");            break;
		case S_IFSOCK: printf("socket\n");                  break;
		default:       printf("unknown?\n");                break;
	}

	printf("I-node number:            %ld\n", (long) st.st_ino);

	printf("Mode:                     %lo (octal)\n", (unsigned long) st.st_mode);

	printf("Link count:               %ld\n", (long) st.st_nlink);
	printf("Ownership:                UID=%ld   GID=%ld\n", (long) st.st_uid, (long) st.st_gid);

	printf("Preferred I/O block size: %ld bytes\n", (long) st.st_blksize);
	printf("File size:                %lld bytes\n", (long long) st.st_size);
	printf("Blocks allocated:         %lld\n", (long long) st.st_blocks);

	printf("Last status change:       %s", ctime(&st.st_ctime));
	printf("Last file access:         %s", ctime(&st.st_atime));
	printf("Last file modification:   %s", ctime(&st.st_mtime));

	exit(EXIT_SUCCESS);
}
