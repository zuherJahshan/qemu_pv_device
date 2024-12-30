#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char **argv)
{
	char *p;
	int fd;

	fd = open("/dev/zcdrv_0", O_RDWR);
	if (fd < 0) {
		printf("open %d\n", fd);
		return 1;
	}

	p = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (!p) {
		printf("mmap\n");
		return 1;
	}

	printf("%s\n", p);

	if (argc == 2) {
		strcpy(p, argv[1]);
	printf("%s\n", p);
	}

	munmap(p, 1024);

	close(fd);

	return 0;
}
