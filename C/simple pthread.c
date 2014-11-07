#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */


typedef struct {
  int x, y;
} Point;

Point scalarTwo(void *A){
  Point temp = *( (Point *)A ) ; 
  Point res; 
  res.x = 2*temp.x;
  res.y = 2*temp.y;
  return res;
}




/* function to be executed by the new thread */
void* do_loop(void* data){
    int i;			/* counter, to print numbers */
    int j;			/* counter, for delay        */
    int me = *((int*)data);     /* thread identifying number */

    for (i=0; i<10; i++) {
	for (j=0; j<500000; j++) /* delay loop */   
        printf(" '%d' - Got '%d'\n", me, i);
    }
    /* terminate the thread */
    pthread_exit(NULL);
}

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[]){
    int        thr_id;         /* thread ID for the newly created thread */
    pthread_t  p_thread;       /* thread's structure                     */
    int        a         = 1;  /* thread 1 identifying number            */
    int        b         = 2;  /* thread 2 identifying number            */

    /* create a new thread that will execute 'do_loop()' */
    thr_id = pthread_create(&p_thread, NULL, do_loop, (void*)&a);

	printf(" Here the current thread id!  %d \n" , thr_id); 
    /* run 'do_loop()' in the main thread as well */
    do_loop((void*)&b);
    
	return 0;
}




