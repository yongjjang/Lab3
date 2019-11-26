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
    if ((shmd = shm_open(SHMNAME, O_RDWR, 0666)) 
        == -1) {
        perror ("shm_open failed");
        exit (1);
    }
    if ((shmaddr = mmap(0, SHMSIZE, PROT_READ, 
    MAP_SHARED, shmd, 0)) == MAP_FAILED) {
        perror ("mmap failed");
        exit (1);
    }
    if (mlock(shmaddr, SHMSIZE) != 0) {
        perror ("mlock failed");
        exit (1);
    }
    printf("received from shared memory : %s\n", (char 
    *)shmaddr);
    if (munmap(shmaddr, SHMSIZE) == -1) {
        perror ("munmap failed");
        exit (1);
    }
    close(shmd);
    if (shm_unlink(SHMNAME) == -1) {
        perror ("shm_unlink failed");
        exit (1);
    }
}
