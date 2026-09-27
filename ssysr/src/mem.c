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

  fgets(total.lineStr, sizeof(total.lineStr), fpmem);
  fgets(mfree.lineStr, sizeof(mfree.lineStr), fpmem);
  fgets(avail.lineStr, sizeof(avail.lineStr), fpmem);


  sscanf(total.lineStr,"%*s %f", &total.num);
  sscanf(mfree.lineStr,"%*s %f", &mfree.num);
  sscanf(avail.lineStr,"%*s %f", &avail.num);

  (*pTotal) = total.num / kbToGib;
  (*pAvai)  = avail.num / kbToGib;
  (*pUsed)  = (total.num - avail.num) / kbToGib;
  (*Pprc)   = (avail.num/total.num ) * 100;


  fclose(fpmem);
}





