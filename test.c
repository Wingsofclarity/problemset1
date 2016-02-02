#include <unistd.h>
#include <stdio.h>

int main(void) {
  char *const cmd[] =  {"ls", "-l", NULL};
  execvp(cmd[0], cmd);
  fork();
  puts("Hje");
}
