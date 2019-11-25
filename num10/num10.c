/* readshm.c */
/* POSIX shared memory example */
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


#define SHMSIZE 2048
#define SHMNAME "/my_shm"



void main(int argc, char* argv[])
{
  FILE *fp, *copy_fp;
  char *path = argv[1];
  char buf[SHMSIZE];
  int status, shmd, count;
  void *shmaddr;
  pid_t pid;

  memset(buf, 0, SHMSIZE);

  if((pid = fork()) == 0){
    /* chile write*/

    if ((shmd = shm_open(SHMNAME, O_CREAT | O_RDWR, 0666)) == -1) {
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

    if((fp = fopen(path, "r")) == NULL){
      perror("fopen");
      exit(1);
    }

    while(feof(fp) == 0){
      count == fread(buf, sizeof(char), SHMSIZE, fp);
      strcpy((char *)shmaddr, buf);      
      //printf("%s",buf);
    }

    if (munmap(shmaddr, SHMSIZE) == -1) {
      perror ("munmap failed");
      exit (1);
    }
    
    fclose(fp);

  }else if (pid > 0){
    /* parents read */
    pid = wait((int *) 0);

    if ((shmd = shm_open(SHMNAME, O_RDWR, 0666)) == -1) {
      perror ("shm_open failed");
      exit (1);
    }
  
    if ((shmaddr = mmap(0, SHMSIZE, PROT_READ, MAP_SHARED, shmd, 0)) == MAP_FAILED) {
      perror ("mmap failed");
      exit (1);
    }
  
    if (mlock(shmaddr, SHMSIZE) != 0) {
      perror ("mlock failed");
      exit (1);
    }


    strcat(path,"_copy");

    if((copy_fp = fopen(path, "w")) == NULL){
      perror("fopen");
      exit(1);
    }

    fwrite(shmaddr, sizeof(char), SHMSIZE, copy_fp);
    fclose(copy_fp);


    //printf("received from shared memory : %s\n", (char *)shmaddr);
  
    if (munmap(shmaddr, SHMSIZE) == -1) {
      perror ("munmap failed");
      exit (1);
    }
  
    close(shmd);
  
    if (shm_unlink(SHMNAME) == -1) {
      perror ("shm_unlink failed");
      exit (1);
    }

    
  }else{
    perror("fork Error");
    exit(1);
  }
}
