#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(void)
{
        FILE *fp;

        if ( (fp = fopen("/etc/shadow", "r")) )
                printf("REPORT: File opened successfully\n");
        else

				errno = 25;
				perror("error? " );
				printf("ERROR: %s\n", strerror(errno));
				puts("MOAR ERROR");
        return 0;
}

/* errno is kind of like a global variable that we can print out  and set based on diffferent errors that hapen inside our c programs, it can be useful because we can figure out EXACTLY what has happened instead of the usual segmentation fault. 


when we run this program we will get the following outpus. 

 gcc -o errno errno.c 
 ./errno 
 error? : Inappropriate ioctl for device




"Inappropriate ioctl for device" is the errno code for 25. set by a macro included in the errno.h header. It's really just for the convenience of the programmer to have a standard set of errors so that other programmers who know the errno codes can have an easier time debugging someone else's code. yay. 



tl; dr we set errno to 25 in line 13, perror prints out your personal error messsage followed by the error message for 25.  


*/
