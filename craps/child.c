#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> /* read(), write() calls */
#include <stdio.h>
#include "child.h"

struct child{
  int pid;
  int dice_value;
  pipe_t from_child;
  pipe_t to_child;
};

child_t child_new(int pid, pipe_t ato_child, pipe_t afrom_child){
  child_t c = malloc(sizeof(child_t));
  child_set_pid(c,pid);  
  c->to_child=ato_child;
  c->from_child=afrom_child;
  c->dice_value=0;
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

void child_write_int(child_t c, int i){
  if(write(child_get_to(c), &i, sizeof(int))!=sizeof(int)){
    perror("Error in write to pipe.");
    exit(0);
  }
}

void child_write(child_t c, void *p){
  write(child_get_to(c), p, sizeof(int));
}

int child_read_int(child_t c){
  int *i=0;
  if (read(child_get_from(c),i,sizeof(int))!=sizeof(int)){
    perror("Read fail.\n");
    exit(0);
  }
  return *i;
}

void child_set_dice(child_t c, int a){
  c->dice_value=a;
}

int child_get_dice(child_t c){
  return c->dice_value;
}
