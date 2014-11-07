
#include <stdio.h>



int main() {

// \x1b[ %d, %d]  \x1b   //this is an escape sequence
 //the first %d is the control 

//printf( \x1b[2;31;41m    \x1b[0m )



 printf( "\x1b[31m     This text is RED!  \x1b[0m \n");
 //printf(ANSI_COLOR_RED   "This text is RED!"   ANSI_COLOR_RESET "\n");


}
