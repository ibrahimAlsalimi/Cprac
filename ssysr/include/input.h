// input.h
#ifndef INPUT_H
#define INPUT_H

//extrn volatile int running;
extern volatile int running;

void handle_sigint(int sig);
void* keyboard_listener(void *arg);



#endif // !INPUT_H
