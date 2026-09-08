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

#define MEM_INFO_PATH "/proc/meminfo"

 
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
  float used, avi, tot, pr = 0;

  fetch_Mem_Info(&tot, &avi, &used, &pr);
  printf("\rTotal = %.2f GiB\tUsed = %.2f GiB\t\tAvailble = %.2f GiB\t\t%%%.2f\0", tot, used, avi, 100 - pr);  
  
  return 0;
}
