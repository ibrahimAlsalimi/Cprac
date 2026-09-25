/*
 * - make the args and flow of cantrol
 * - start donig cpu
 *
 *  "why say many words when few can do trick"
 *      - kevin malone
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <pthread.h>
#include <signal.h>


#include "mem.h"
#include "term.h"
#include "ui.h"
#include "input.h"

// #define ESC "\033"
#define CPU_STATS_PATH "/proc/stat"


typedef enum MetricType{
  RAM,
  CPU,
  NETWORK
} MetricType;

/*
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

*/
int main(int argc, char *argv[]){
  enable_row_mode();
  signal(SIGINT, handle_sigint);
  pthread_t listener_thread;
  pthread_create(&listener_thread, NULL, keyboard_listener, NULL);

  float used, avi, tot, pr = 0;

  print_funcs(ENTER_BUFFER_SCREEN);
  print_funcs(CLEAR);
  print_funcs(HIDE_CURSOR);

  while (running) {

    fetch_Mem_Info(&tot, &avi, &used, &pr);
    print_funcs(CLEAR);
    printf("Total     =   %.2f GiB\nUsed      =   %.2f GiB\nAvailble  =   %.2f GiB\n", tot, used, avi);
    print_bar("used", pr);

    fflush(stdout);
    usleep(250000);
   }


   print_funcs(EXIT_BUFFER_SCREEN);
    print_funcs(RESTORR_CRUSOR);
    //printf(ESC "[2J" ESC "[H");
  fflush(stdout);
  pthread_join(listener_thread, NULL);
  return 0;
}
