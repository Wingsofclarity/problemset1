#ifndef CHILD_H_
#define CHILD_H_

typedef struct child child_t;

child_t child_new();

void child_set_pid(child_t*, int);

int child_get_pid(child_t*);

#endif
