// ui.c

#include "ui.h"
#include <stdio.h>




void print_funcs(prin cs){     // refrech print
  switch (cs) {
    case CLEAR:
     printf(ESC "[2J" ESC "[H");
    break;

    case HIDE_CURSOR:
     printf(ESC "[?25l");
    break;

    case RESTORR_CRUSOR:
     printf(ESC "[?25h");
    break;

    case ENTER_BUFFER_SCREEN:
      printf(ESC "[?1049h");
    break;

    case EXIT_BUFFER_SCREEN:
      printf(ESC "[?1049l");
    break;

    default:
      break;
  }
}


void print_bar(char *name, double pr, int min){
    char bar[10] = "..........";
    if (min > 0 ) pr = min - pr;
    float pr2 = pr/10;
    for(int i = 0; i < pr2; i++) bar[i] = '#';
    printf("%s\t[ %s ]\t%%%.2f\n", name, bar, pr);
}
