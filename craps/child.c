#include <stdlib.h>
#include <stdbool.h>
#include "child.h"

struct child{
  int pid;
  pipe_t from_child;
  pipe_t to_child;
};

child_t child_new(int pid, pipe_t afrom_child, pipe_t ato_child){
  child_t c;
  child_set_pid(c,pid);  
  c->to_child=ato_child;
  c->from_child=afrom_child;
  return c;
}

int child_get_pid(child_t c){
  return c->pid;
}

void child_set_pid(child_t c, int a){
  c->pid=a;
}

void child_free(child_t c){
  free(c);
  return;
}
