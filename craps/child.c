#include <stdlib.h>
#include <stdbool.h>
#include "child.h"

struct child{
  int pid;
  //todo: nPipes
};

child_t child_new(int a){
  child_t c;
  
  return c;
}

int child_get_pid(child_t* c){
  return c->pid;
}

void child_set_pid(child_t* c, int a){
  c->pid=a;
}
