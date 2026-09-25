// term.c 
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "term.h"


termios orig_termios;

void restore_terminal(){
  tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}


void enable_row_mode(){
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(restore_terminal);

  termios raw = orig_termios;
  raw.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}
