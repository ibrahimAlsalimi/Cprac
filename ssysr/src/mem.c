#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#define MEM_INFO_PATH "/proc/meminfo"



void fetch_Mem_Info(float *pTotal, float *pAvai, float *pUsed, float *Pprc){
  FILE *fpmem = fopen(MEM_INFO_PATH, "r");
    if(fpmem == NULL) {     // this looks bad for now but idk how to do it, work on that letar
      printf("null\n");
      // exit; // i think it should be some pointer on a golbal var to chcek if the file open or not here
    }
    int kbToGib = 1024 * 1024;

    mem  total;
    mem  mfree;
    mem  avail;

    // total.type, mfree.type, avail.type = RAM;

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





