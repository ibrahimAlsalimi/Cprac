/*
 *  - rewrite the code agine 
 *  - i will isolte the code blocks and make a function fo every thing 
 *  - it wolud have args and it eill do multiple things like show the live use fo resoueres
 *  - -try make it clean ans safe as much as i can 
 *
 *  bugs = 
 *    there id a ovreflow bug in the struct i guss
 *
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MEM_INFO_PATH "/proc/meminfo"

 
typedef enum MetricType{
  RAM,
  CPU,
  NETWORK
}MetricType;


typedef struct mem{
  MetricType type;
  char  str[8];
  char  lineStr[48];
  int   strsize;
  float num;
  int   line;

} mem;


int memStr_to_int(char *str, int size){
  char buff[27] = {0};
  int t = 0;
  
   for (int i = 0; str[i] != '\0' && t < (int)sizeof(buff) - 1; i++) {
      if (str[i] >= '0' && str[i] <= '9') {
          buff[t++] = str[i];
      }
   }
     buff[t] ='\0';

    long value = atoi(buff);
  return value;
}


void fetch_Mem_Info(float *pTotal, float *pAvai, float *pUsed, float *Pprc){
  FILE *fpmem = fopen(MEM_INFO_PATH, "r");
    if(fpmem == NULL) {
      printf("null\n");
      exit; 
    }
    int kbToGib = 1024 * 1024;
    mem  total;
    mem  mfree;
    mem  avail;
     
    total.line = 0;
    mfree.line = 1;
    avail.line = 2;


  for (int i = 0; i < 3; i++ ){
    if(i == 0) fgets(total.lineStr, sizeof(total.lineStr), fpmem);
    if(i == 1) fgets(mfree.lineStr, sizeof(mfree.lineStr), fpmem);
    if(i == 2) fgets(avail.lineStr, sizeof(avail.lineStr), fpmem);
    
  }

  total.num = memStr_to_int(total.lineStr, strlen(total.lineStr)); 
  mfree.num = memStr_to_int(mfree.lineStr, strlen(mfree.lineStr));
  avail.num = memStr_to_int(avail.lineStr, strlen(avail.lineStr)); 
  
  (*pTotal) = total.num / kbToGib;
  (*pAvai)  = avail.num / kbToGib;
  (*pUsed)  = (total.num - avail.num) / kbToGib;
  (*Pprc)   = (avail.num/total.num ) * 100;


 // printf("memtotal = %d   memfree = %d    memavailable = %d", total.num, mfree.num, avail.num);
  fclose(fpmem);
} 

void calc_Cpu_Use(){  

}

void print_ref(){     // refrech print

}


int main(int argc, char *argv[]){
  float used, avi, tot, pr = 0;

  fetch_Mem_Info(&tot, &avi, &used, &pr);
  printf("\rTotal = %.2f GiB\tUsed = %.2f GiB\t\tAvailble = %.2f GiB\t\t%%%.2f\0", tot, used, avi, 100 - pr);  
  
  return 0;
}
