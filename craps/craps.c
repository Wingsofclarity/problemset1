/**
 * Game of luck: Implementation of the Gamemaster
 *
 * Course: Operating Systems and Multicore Programming - OSM lab
 * assignment 1: game of luck.
 *
 * Author: Nikos Nikoleris <nikos.nikoleris@it.uu.se>
 *
 * History
 *
 * 2016-01-31 (Mahdad Davari)
 *
 * Added more annotations and fine-grained TODO lists 
 *
 */

#include <stdio.h>
#include <stdlib.h> /* rand(), srand() */
#include <unistd.h> /* read(), write() calls */
#include <assert.h>
#include <time.h>   /* time() */
#include <signal.h> /* kill(), raise() and SIG???? */
#include "child.h"

#include <sys/types.h> /* pid */
#include <sys/wait.h> /* waitpid() */

#include "common.h"
#define NUM_PLAYERS 8

int main()
{
  int i, seed;
  int read_from_here;

  //char arg0[] = "./shooter"; 
  //char arg1[10]; 
  //char *args[] = {arg0, arg1, NULL};

  child_t *children = malloc(sizeof(child_t)*NUM_PLAYERS);
  
  for (i = 0; i < NUM_PLAYERS; i++) {
    int *pipe_seed=malloc(sizeof(int)*2);
    int *pipe_score=malloc(sizeof(int)*2);
    pipe(pipe_seed);
    pipe(pipe_score);


    //fprintf(stderr, "For %i Seed %i -> %i \n", i, pipe_seed[1],pipe_seed[0]);
    //fprintf(stderr, "For %i Score %i -> %i \n", i , pipe_score[1], pipe_score[0]);
    
    int pid = fork();
    
    if (pid == 0 ){
      close(pipe_seed[1]);
      close(pipe_score[0]);
      shooter(i,pipe_seed[0],pipe_score[1]);
      return 0;
    }
    else if (pid>0){
      close(pipe_seed[0]);
      close(pipe_score[1]);
      read_from_here=pipe_score[0];
      children[i] = child_new(pid,pipe_seed[1],pipe_score[0]);
    }
    else if (pid==-1){
      puts("Child could not be created.");
      return -1;
    }
    else {
      puts("Unknown error.");
      return -1;
    }
  }

  for (int i = 0; i<NUM_PLAYERS; i++){
  }

  
  seed = time(NULL);



  for (i = 0; i < NUM_PLAYERS; i++) {
    seed++;
    child_write_int(children[i],seed);
  }

  sleep(5);
  for (i = 0; i < NUM_PLAYERS; i++) {
    child_set_score(children[i], child_read_int(children[i]));
  }
  
  int winner_index=0;  
  for (i = 1; i < NUM_PLAYERS; i++) {
    if(child_get_score(children[i])>child_get_score(children[winner_index])){
      winner_index=i;
    }
  }

  
  printf("PARENT: master: player %i WINS\n", winner_index);
  

  // TODO 7: signal the winner
  //         - which command do you use to send signals?
  //         - you will need the pid of the winner
  int winner_pid=child_get_pid(children[winner_index]);
  sleep(3);
  kill(winner_pid, SIGUSR1);
	

  // TODO 8: signal all players the end of game
  //         - you will need the pid of all the players

    
  for (i = 0; i < NUM_PLAYERS; i++) {
    kill(child_get_pid(children[i]), SIGUSR2);
  }
  for (i = 0; i < NUM_PLAYERS; i++) {
    int exit_pid = wait(0);
    fprintf(stderr, "PARENT: PID %i has exited\n",exit_pid);
  }

  printf("PARENT: master: the game ends\n");


  // TODO 9: cleanup resources and exit with success
  //         wait for all the players/children to exit
  //         before game master exits 

  for (i = 0; i < NUM_PLAYERS; i++) {
    child_free(children[i]);
  }

  puts("PARENT: Craps exiting properly.");
  return 0;
}
