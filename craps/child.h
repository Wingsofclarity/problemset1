#ifndef CHILD_H_
#define CHILD_H_

typedef struct child* child_t;
typedef int* pipe_t;

child_t child_new(int, pipe_t, pipe_t);

void child_set_pid(child_t, int);

int child_get_pid(child_t);

void child_free(child_t);

#endif
