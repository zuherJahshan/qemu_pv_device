// mmap_example.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define DEVICE "/dev/zcdrv_0"
#define PAGE 4096 // 4KB
#define SIZE (10*PAGE) // 10 pages

int main() {
    unsigned long offset = PAGE;
    int fd = open(DEVICE, O_RDWR);
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }

    void *addr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return EXIT_FAILURE;
    }

    void *ptr = addr + offset;

    /* Write data */
    strcpy((char *)ptr, "Hello, zcdrv!");
    printf("Written to device: %s\n", (char *)ptr);

    /* Read data */
    printf("Read from device: %s\n", (char *)ptr);

    munmap(addr, SIZE);
    close(fd);
    return EXIT_SUCCESS;
}
