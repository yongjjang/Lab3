#include <unistd.h>


void main(int argc, char* argv[])
{
  if(argc == 1)
    {
      printf("Usage: %s <exec command> , [arg0, arg1, arg2, ...]\n", argv[0]);
      return 1;
    }

  pid_t pid = fork();
  if(pid < 0)
    {
      perror("fork error");
      return 1;
    }

  if(pid == 0)
    {
      wait(0);
    }
  else
    {
      execvp(argv[1],argv+1);
      return 0;
    }
}
