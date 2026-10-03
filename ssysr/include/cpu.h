#ifndef CPU_H
#define CPU_H

typedef struct cpuSam{
    char name[8];
    unsigned long long user,  nice, system,  idle;
    unsigned long long iowait, irq, softirq, steal, guest, nice_guset;
    unsigned long long sam_core_usage;
} cpuSam;


typedef struct cpuCore{

  int    id;
  cpuSam prev;
  cpuSam cur;
  double usage;
} cpuCore;


typedef struct cpuMon {
  
  int     core_count;
  cpuCore total;
  cpuCore *core;

} cpuMon;


int calccpu();
void asinn(cpuMon *cpu);
void staToInt(char *lin, cpuSam *m);
void sumCores(cpuSam *m);
void getSexy(cpuMon *cpuu);
void readFile(cpuMon *re, int count);
void getUsage(cpuMon *cpuu);
void print_cpu_core_usage(cpuMon *cpu);
void freeall(cpuMon *cpuu);
void initold(cpuMon *cpuu);

#endif // !CPU_H
