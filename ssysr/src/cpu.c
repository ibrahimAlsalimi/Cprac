#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cpu.h"


#define CPU "/proc/stat"


int calccpu(){
  int cpu_count = 0;
  char line[64];
  int run = 1;

  FILE *fp = fopen(CPU, "r");
  if(fp == NULL) run = 0;
   
  while(run == 1) { 
    fgets(line, sizeof(line), fp); 
    if (strncmp(line, "cpu", 1) == 0) cpu_count++;
    else run = 0;
  }


  fclose(fp);

  return cpu_count;
}


void asinn(cpuMon *cpu){

  cpu->core_count = calccpu();
  cpu->core = malloc(cpu->core_count * sizeof(cpuCore));


}

void strToInt(char *lin, cpuSam *m){
   sscanf(lin, "%s %llu %llu %llu %llu %llu %llu %llu",  
                  &m->name, &m->user, &m->nice, &m->system, &m->idle,
                  &m->iowait, &m->irq, &m->softirq, &m->steal, &m->guest, &m->nice_guset);

}
void sumCores(cpuSam *m){

  m->sam_core_usage = m->user + m->nice + m->system + m->idle + m->iowait + m->irq + m->softirq + m->steal + m->guest + m->nice_guset;
}
void readFile(cpuMon *re, int count){
  FILE *fpr = fopen(CPU, "r");

  char line[64];

  for (int i = 0; i < count; i++) {
  fgets(line, sizeof(line), fpr);
  strToInt(line, &re->core[i].cur);
   
   sumCores(&re->core[i].cur);
  }

   fclose(fpr);
}


void freeall(cpuMon *cpu){
  free(cpu->core);
}




void initold(cpuMon *cpuu){
  for (int i = 0; i < cpuu->core_count; i++) {
    cpuu->core[i].prev = cpuu->core[i].cur;

 }
}

double getSexy(cpuMon *cpuu){

    int i = 0;

    asinn(cpuu);
    int co = cpuu->core_count;
     readFile(cpuu, cpuu->core_count);
    initold(cpuu);
    readFile(cpuu, cpuu->core_count);

    unsigned long long dt;
    unsigned long long di;
    double useg;

      dt = cpuu->core[i].cur.sam_core_usage - cpuu->core[i].prev.sam_core_usage;
      di = (cpuu->core[i].cur.idle + cpuu->core[i].cur.iowait) - (cpuu->core[i].prev.idle + cpuu->core[i].prev.iowait);
      useg = (1.0 - (double)di / (double)dt ) * 100;


      return useg;
} 
