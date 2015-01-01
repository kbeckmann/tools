#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void run_code(char *buf) {
	(*(void(*)()) buf)();
}

void run_file(char *fname) {
	FILE* fp;
	int fd;
	off_t file_size;
	char *buffer;
	struct stat st;

	fd = open(fname, O_RDONLY);
	if (fd == -1) {
		printf("open(%s) failed\n", fname);
	}

	fp = fdopen(fd, "rb");
	if (fp == NULL) {
		printf("fdopen() failed\n");
	}
 
	/* Ensure that the file is a regular file */
	if ((fstat(fd, &st) != 0) || (!S_ISREG(st.st_mode))) {
		printf("fstat() failed, file is not regular\n");
	}
  
	if (fseeko(fp, 0 , SEEK_END) != 0) {
		printf("fseeko() failed\n");
	}
   
	file_size = ftello(fp);
	if (file_size == -1) {
		printf("file_size == -1\n");
	}
	  
	buffer = (char*)malloc(file_size);
	if (buffer == NULL) {
		printf("malloc(%d) failed\n", (int)file_size);
	}

	fseeko(fp, 0, SEEK_SET);

	while (fread(buffer, file_size, 1, fp) > 0);

	printf("Successfully read [%d] bytes.\n", (int)file_size);

	run_code(buffer);
}

void print_help(char *s) {
	printf(
	"\n"
	"Usage: %s [-f <file> | -e <code>]\n"
	"\n"
	"exec_shellcode makes it easy to try out shellcode locally. You can quickly execute code that is stored in an environment variable or you could run something that contains null characters etc from a file.\n"
	"\n"
	"Options:\n"
	"\t-f reads the binary file <file> and executes it.\n"
	"\t-e executes the argument <code> directly.\n"
	"\n"
	, s);
}

int main(int argc, char **argv) 
{
	if (argc != 3) {
		print_help(argv[0]);
		return -1;
	}

	if (!strcmp("-f", argv[1])) {
		run_file(argv[2]);
	} else if (!strcmp("-e", argv[1])) {
		run_code(argv[2]);
	} else {
		print_help(argv[0]);
		return -1;
	}

	return 0;
}

