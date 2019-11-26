#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#define SHMSIZE 1024
#define SHMNAME "/my_shm"
int main()
{
    int shmd, len;
    void *shmaddr;
    if ((shmd = shm_open(SHMNAME, O_CREAT | 
        O_RDWR, 0666)) == -1) {
        perror ("shm_open failed");
        exit (1);
    }
    if (ftruncate(shmd, SHMSIZE) != 0) {
        perror ("ftruncate failed");
        exit (1);
    }
    if ((shmaddr = mmap(0, SHMSIZE, PROT_WRITE,
        MAP_SHARED, shmd, 0)) == MAP_FAILED) {
        perror ("mmap failed");
        exit (1);
    }
    if (mlock(shmaddr, SHMSIZE) != 0) {
        perror ("mlock failed");
        exit (1);
    }
    strcpy((char *)shmaddr, "Hello, inan");
    if (munmap(shmaddr, SHMSIZE) == -1) {
        perror ("munmap failed");
        exit (1);
    }
    close(shmd);
}

