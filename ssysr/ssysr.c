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
  char str[8];
  char lineStr[48];
  int  strsize;
  long long num;
  int  line;

} mem;


int memStr_to_int(char *str, int size){
  char buff[32];
  int t = 0;
    for(int i = 0; i < size; i++){
      if(str[i] >= 48 && str[i] <= 57){
          buff[t] = str[i];
          t++;
           }
      }


  return atoi(buff);
}


void fetch_Mem_Info(int *pTotal, int *pAvai, int *pUsed, float *Pprc){
  FILE *fpmem = fopen(MEM_INFO_PATH, "r");
    if(fpmem == NULL) printf("null\n");

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

  total.num = memStr_to_int(total.lineStr, sizeof(total.lineStr));
  mfree.num = memStr_to_int(mfree.lineStr, sizeof(mfree.lineStr));
  avail.num = memStr_to_int(avail.lineStr, sizeof(avail.lineStr));
  
  (*pTotal) = total.num;
  (*pAvai)  = avail.num;
  (*pUsed)  = total.num - avail.num;
  (*Pprc)   = avail.num/total.num;


  //printf("t = %d\tf = %d\ta = %d", total.num, mfree.num, avail.num);
  fclose(fpmem);
} 

void calc_Cpu_Use(){  

}

void print_ref(){     // refrech print

}


int main(int argc, char *argv[]){
  int used, avi, tot = 0;
  float pr = 0;

  fetch_Mem_Info(&tot, &avi, &used, &pr);
  printf("t = %d\tavi =%d\tused = %d\tpr = %f\n", tot, avi, used, pr);  
  return 0;
}
