#include <stdlib.h>
#include <stdbool.h>
#include "child.h"

struct child{
  int pid;
  pipe_t from_child;
  pipe_t to_child;
};

child_t child_new(int pid, pipe_t afrom_child, pipe_t ato_child){
  child_t c = malloc(sizeof(child_t));
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

int child_get_from(child_t c){
  return (int) c->from_child;
}

int child_get_to(child_t c){
  return (int) c->to_child;
}
