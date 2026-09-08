/*
 * - need to make it live by useing threds  
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

#define ESC "\033"
#define MEM_INFO_PATH "/proc/meminfo"

 
typedef struct termios termios;
termios orig_termios;


volatile int running = 1;


typedef enum MetricType{
  RAM,
  CPU,
  NETWORK
}MetricType;


typedef struct mem{
  MetricType type;
  char  lineStr[48];
  float num;
  int   line;
} mem;


void restore_terminal(){
  tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}


void enable_row_mode(){
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(restore_terminal);

  termios raw = orig_termios;
  raw.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}


void handle_sigint(int sig){
  (void)sig;

  running = 0;
  printf("\n CTRL + C \n");
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


int memStr_to_int(char *str){
  char buff[27] = {0};
  int t = 0;
  long return_value;
  
  for (int i = 0; str[i] != '\0' && t < (int)sizeof(buff) - 1; i++) {   // it take the number in the string and save it 
      if (str[i] >= '0' && str[i] <= '9') {
          buff[t++] = str[i];
      }
  }
    
  buff[t] ='\0';

  return_value = atoi(buff);
  return return_value;
}


void fetch_Mem_Info(float *pTotal, float *pAvai, float *pUsed, float *Pprc){
  FILE *fpmem = fopen(MEM_INFO_PATH, "r");
    if(fpmem == NULL) {     // this looks bad for now but idk how to do it, work on that letar
      printf("null\n");
      exit; // i think it should be some pointer on a golbal var to chcek if the file open or not here
    }
    int kbToGib = 1024 * 1024;
    
    mem  total;
    mem  mfree;
    mem  avail;
  
    total.type, mfree.type, avail.type = RAM;

    total.line = 0;
    mfree.line = 1;
    avail.line = 2;


  for (int i = 0; i < 3; i++ ){
    if(i == total.line) fgets(total.lineStr, sizeof(total.lineStr), fpmem);
    if(i == mfree.line) fgets(mfree.lineStr, sizeof(mfree.lineStr), fpmem);
    if(i == avail.line) fgets(avail.lineStr, sizeof(avail.lineStr), fpmem);
    
  }

  total.num = memStr_to_int(total.lineStr); 
  mfree.num = memStr_to_int(mfree.lineStr);
  avail.num = memStr_to_int(avail.lineStr); 
  
  (*pTotal) = total.num / kbToGib;
  (*pAvai)  = avail.num / kbToGib;
  (*pUsed)  = (total.num - avail.num) / kbToGib;
  (*Pprc)   = (avail.num/total.num ) * 100;


  fclose(fpmem);
} 

void calc_Cpu_Use(){  

}

void calc_Network_Use(){

}

void print_ref(){     // refrech print

}


int main(int argc, char *argv[]){
  enable_row_mode();
  signal(SIGINT, handle_sigint);
  pthread_t listener_thread;
  pthread_create(&listener_thread, NULL, keyboard_listener, NULL);

  float used, avi, tot, pr = 0;
  printf(ESC "[?25l");

  while (running) {
  
    fetch_Mem_Info(&tot, &avi, &used, &pr);
    printf(ESC "[2J" ESC "[H");
    printf("\rTotal     =   %.2f GiB\nUsed      =   %.2f GiB\nAvailble  =   %.2f GiB\t\t%%%.2f", tot, used, avi, 100 - pr);  
    fflush(stdout);
    usleep(250000);
   }
    printf(ESC "[?25h");
    printf(ESC "[2J" ESC "[H");
  fflush(stdout);
  pthread_join(listener_thread, NULL);
  return 0;
}
