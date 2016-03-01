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
#define NUM_PLAYERS 1

//int main(int argc, char *argv[])
int main()
{
  int i, seed;

  // TODO 1: Un-comment the following variables to use them in the 
  //         exec system call. Using the function sprintf and the arg1 
  //         variable you can pass the id parameter to the children 

  //char arg0[] = "./shooter"; 
  //char arg1[10]; 
  //char *args[] = {arg0, arg1, NULL};
	

  // TODO 2: Declare pipe variables
  //         - Of which data type should they be?
  //         - How many pipes are needed?
  //         - Try to choose self-explanatory variable names, e.g. seedPipe, scorePipe
  //pipe();
	

  // TODO 3: initialize the communication with the players, i.e. create the pipes

  for (i = 0; i < NUM_PLAYERS; i++) {

  }


  // TODO 4: spawn/fork the processes that simulate the players
  //         - check if players were successfully spawned
  //         - is it needed to store the pid of the players? Which data structure to use for this?
  //         - re-direct standard-inputs/-outputs of the players
  //         - use execv to start the players
  //         - pass arguments using args and sprintf
  child_t *children = malloc(sizeof(child_t)*NUM_PLAYERS);
  
  for (i = 0; i < NUM_PLAYERS; i++) {
    int *pipe_seed=malloc(sizeof(int)*2);
    int *pipe_score=malloc(sizeof(int)*2);
    pipe(pipe_seed);
    //pipe(pipe_score);
    pipe_score[0]=0;
    pipe_score[1]=0;

    //Test
    /*
    int wr = 4949;
    write(pipe_seed[1],&wr,sizeof(int));

    int res;
    read(pipe_seed[0],&res,sizeof(int));
    fprintf(stderr, "We read this number.. %i from %i \n", res, pipe_seed[0]);
    */
    //Test end

    fprintf(stderr, " seed[0]: %i \n seed[1]: %i \n score[0]: %i \n score[1]: %i \n",pipe_seed[0],pipe_seed[1], pipe_score[0], pipe_score[1]);
    
    int pid = fork();

    if (pid == 0 ){
      //printf("I am a child. Initiating execv. \n");
      //execv(arg0, args);
      shooter(pid,pipe_seed[0],pipe_score[1]);
      return 0;
    }
    else if (pid>0){
      printf("I am the parent who just spawned %i.\n", pid);
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
    fprintf(stderr, "Proccess in spot %i has pid %i. I will read from %i and write to %i. \n", i, child_get_pid(children[i]), child_get_from(children[i]), child_get_to(children[i]));
  }
  
  seed = time(NULL);


  for (i = 0; i < NUM_PLAYERS; i++) {
    seed++;
    child_write_int(children[i],seed);
  }




  // TODO 6: read the dice results from the players via pipes, find the winner
  int winner_index=0;
  for (i = 1; i < NUM_PLAYERS; i++) {
    if(child_read_int(children[i])>child_read_int(children[winner_index])){
      winner_index=i;
    }
  }
  
  printf("master: player %i WINS\n", winner_index);
  

  // TODO 7: signal the winner
  //         - which command do you use to send signals?
  //         - you will need the pid of the winner

	

  // TODO 8: signal all players the end of game
  //         - you will need the pid of all the players

  for (i = 0; i < NUM_PLAYERS; i++) {

  }


  printf("master: the game ends\n");


  // TODO 9: cleanup resources and exit with success
  //         wait for all the players/children to exit
  //         before game master exits 

  for (i = 0; i < NUM_PLAYERS; i++) {
  }

  puts("Craps exiting properly.");
  return 0;
}
