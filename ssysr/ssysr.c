#include <stdio.h>
#include <unistd.h>

#define WORD8 8

int Str_to_int(char ch, int count){
  int ret_val = ch - 48;
  
  if(ch >= 48){
  for(int i = count; i >= 1; i--) ret_val *= 10;
    }
  
  else ret_val = 0; 

  return ret_val;
}



int main(){

  float KbToGib = 1024 * 1024;


      while (true) {
  FILE *fpCpu = fopen("/proc/meminfo", "r");
  if(fpCpu == NULL){
    perror("can't open /proc/meminfo");
    return 1;  
  }

  char ln_buff[32];
  
  char total_Mem[WORD8];
  float tMem;
  

  char mem_Avi[16];
  float aviMem;


  for(int i = 0; i < 3; i++){
    fgets(ln_buff, sizeof(ln_buff), fpCpu);
    int col = 0;
    int spc = -1;
    int start_point = 1;

    for(int c = 0; c < sizeof(ln_buff); c++){
      if(ln_buff[c] == ':') col = c;
      if(ln_buff[c] == ' ') spc++;


    }
    

    start_point += col + spc;
    for(int k = 0; k < 8; k++){
      if(i == 0) total_Mem[k]  = ln_buff[start_point + k];
      if(i == 2) mem_Avi[k]    = ln_buff[start_point + k];
    }
  }
  

  fclose(fpCpu);
  
  for(int i = 7; i >= 0; i--){
      tMem += Str_to_int(total_Mem[7-i], i); 
      aviMem += Str_to_int(mem_Avi[7-i], i); 

    }
    

      //printf("\rtotal Mem = %.2f Gib\t", tMem / KbToGib); 
      //printf("\rAvailable Mem = %.2f Gib\t", aviMem / KbToGib);
      //printf("\rused Mem = %.2f Gib\t", (tMem - aviMem)/KbToGib);
      printf("\r[%%%.2f]\n", ((tMem - aviMem)/tMem)*100);
      fflush(stdout);
      usleep(500000);
    

      }
}
