#ifndef MEM_H
#define MEM_H

typedef struct mem{
  // MetricType type;
  char  lineStr[48];
  float num;
  int   line;
} mem;


void fetch_Mem_Info(float *pTotal, float *pAvai, float *pUsed, float *Pprc);
int memStr_to_int(char *str);

#endif // MEMH
