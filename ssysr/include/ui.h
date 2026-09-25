// ui.h
#ifndef UI_H
#define UI_H

#define ESC "\033"

typedef enum prin{
  CLEAR,
  HIDE_CURSOR,
  RESTORR_CRUSOR,
  ENTER_BUFFER_SCREEN,
  EXIT_BUFFER_SCREEN
} prin;


void print_funcs(prin cs);
void print_bar(char *name, float pr);

#endif 
