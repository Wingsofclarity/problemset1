#include <unistd.h>

int main(void) {
  char *const cmd[] =  {"ls", "-l", NULL};
  execvp(cmd[0], cmd);
  file *file = open("data");
  char *buf = malloc(sizeof(char)*3);
  read(file);
}
