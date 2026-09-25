// input.c 
#include "input.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

// volatile int running = 1;
volatile int running = 1;

void handle_sigint(int sig){
  (void)sig;
  running = 0;
  printf("\n press 'q' to exit\n");
}


void* keyboard_listener(void *arg){
  (void)arg;
  char c;
  while (running) {
   if(read(STDIN_FILENO, &c, 1) == 1){
     if(c == 'q') running = 0;
   }
  }
  return NULL;
}

