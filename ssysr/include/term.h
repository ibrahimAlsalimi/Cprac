// term.h

#ifndef TERM_H
#define TERM_H

 
typedef struct termios termios;
// termios orig_termios;

void restore_terminal();
void enable_row_mode();

#endif // !TERM_H


