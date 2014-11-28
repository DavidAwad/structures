#include	<pthread.h>
#include	<stdio.h>
#include	<unistd.h>
#include  <sys/syscall.h>

/* Test of concurrent access controlled through mutex locks.		*/
/* Test of pthread_mutex_init(), pthread_mutex_lock(),			*/
/* pthread_mutex_unlock()						*/
/*Man pages are for mutex are included in the manpages-posix-dev package! */


// gcc -g -o thread3 thread3.c -lpthread

//pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t	mutex;
int value = 0;

void *worker( void * ignore ){
	printf("tid : %lu got here first.\n",syscall(SYS_gettid));
	int	i;
	int	x;
	for ( i = 0 ; i < 1000 ; i++ ){
		pthread_mutex_lock( &mutex ); //mutex is now locked to whichever thread got there first.
		x = value;
	 	sched_yield(); //"go to some other thread, move away from this one."
		value = x + 1;
		pthread_mutex_unlock( &mutex ); // we UNLOCK the mutex to make it accessible to all of them?
	}
	printf("Thread %lu ends, value is %d.\n", syscall(SYS_gettid) , value ); //we can use syscalls to find the current thread id
	return 0;
}

int main(){
	pthread_t		tid;
	int			i;

	printf( "Cogito ergo sum.\n" );
	pthread_mutex_init( &mutex, NULL );  //initialize the mutex with no weird attributes.
	for ( i = 0 ; i < 2 ; i++ ){
		pthread_create( &tid, 0, worker, 0 );
		/*how does this thread have access to the mutex?
		"they dont, first thread that gets to the unlocked mutex gets to take it."
		 */
	}
	pthread_exit( 0 );
}

/*
  The pthread_mutex_init() function shall initialize the mutex
  by mutex with attributes specified  by  attr.  If  attr  is  NULL,  the
  default  mutex  attributes  are  used;  the effect shall be the same as
  passing the address of a default mutex attributes object. Upon success‐
  ful  initialization,  the  state  of  the mutex becomes initialized and
  unlocked.

  int pthread_mutex_lock(pthread_mutex_t *mutex);
  int pthread_mutex_unlock(pthread_mutex_t *mutex);

  If  successful,  the  pthread_mutex_lock()  and  pthread_mutex_unlock()
  functions  shall  return  zero;  otherwise,  an  error  number shall be
  returned to indicate the error.

  The pthread_mutex_trylock() function shall return zero if a lock on the
  mutex  object referenced by mutex is acquired. Otherwise, an error number
  is returned to indicate the error.
*/
