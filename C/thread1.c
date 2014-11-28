#include	<errno.h>
#include	<malloc.h>
#include	<pthread.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>

// Calculation of greatest common divisor (GCD), multithreaded
// gcc -g -o thread1 thread1.c -lpthread

struct	gcd {
	unsigned int	a,b;
};

unsigned int gcd( unsigned int a, unsigned int b ){	// BKR recursive
	if ( b == 0 )
		return a;
	else
		return gcd( b, a % b );
}

// Note the dynamic memory covenant:  The parent thread allocates the parameter
// struct, the child thread extracts data from the struct and frees it.  For
// return values, the child allocates and the joining thread does the free().

void *gcd_calculator( void * p ){
	struct gcd *	gptr = (struct gcd *)p;
	unsigned int *	rptr;
	rptr = (unsigned int *)malloc( sizeof( unsigned int ) );
	*rptr = gcd( gptr->a , gptr->b ); //pul out what we want from the input parameter.
	free( gptr );
	return rptr;			// Note malloc/free covenant for threads.
}

int main( int argc, char ** argv ){
	pthread_t	tid;
	pthread_attr_t	attr;
	struct gcd *	gcdptr;
	unsigned int *	rptr;
	unsigned int	error;
  //error checks///
	if ( argc < 3 ){
		printf( "Must specify two integer args on command line\n" );
		_exit( 1 );	// crash and burn
	}
	else if ( (gcdptr = (struct gcd *)malloc( sizeof(struct gcd) )) == 0 ){   ///shouldn't we compare to null not zero ?? "Null is zero"
		printf( "malloc() croaked in %s line %d: %s\n", __FILE__ , __LINE__ , strerror( errno ) );
		_exit( 1 );	// crash and burn
	}
	else if ( sscanf( argv[1], " %d", &gcdptr->a ) < 1 ){ //sscanf returns the number of scanned arguments throws it into gcd -> a
		printf( "Must specify two integer args on command line\n" );
		_exit( 1 );	// crash and burn
	}
	else if ( sscanf( argv[2], " %d", &gcdptr->b ) < 1 ){
		printf( "Must specify two integer args on command line\n" );
		_exit( 1 );	// crash and burn
	}
  // here we're done checking the validity of the input  //////////////
	else if ( (error = pthread_attr_init( &attr ))){
		printf( "pthread_attr_init() croaked in %s line %d: %s\n", __FILE__ , __LINE__ , strerror( error ) );
		_exit( 1 );	// crash and burn
	}
	/*
	The  pthread_attr_init()  function  initializes  the thread attributes object pointed to by attr
       with default attribute values.  After this call, individual attributes of the object can be  set
       using  various related functions (listed under SEE ALSO), and then the object can be used in one
       or more pthread_create(3) calls that create threads.

	This check is for what??

	"I'm initializing the attribute I want to pass to a newly created thread."
	"sets them to the default values"

	Where is pthread attr init going to get __FILE and LINE from anyway? ?

	FILE is the source code.
	LINE is the line number it "croaked" at.

	*/
	else if ( (error = pthread_attr_setscope( &attr, PTHREAD_SCOPE_SYSTEM )) != 0 ){
		printf( "pthread_attr_setscope() croaked in %s line %d : %s \n", __FILE__ , __LINE__ , strerror( error ) );
		_exit( 1 );	// crash and burn
	}
	/*
	 The  pthread_attr_setscope()  function  sets  the  contention  scope  attribute  of  the  thread
       attributes  object  referred  to  by attr to the value specified in scope.  The contention scope
       attribute defines the set of threads against which a thread competes for resources such  as  the
       CPU.  POSIX.1-2001 specifies two possible values for scope:

					PTHREAD_SCOPE_PROCESS   //user level thread

					PTHREAD_SCOPE_SYSTEM   //system or kernel level thread  - default

	*/
	else if ( (error = pthread_create( &tid, &attr, gcd_calculator, gcdptr)) ){
		printf( "pthread_create() croaked in %s line %d: %s\n", __FILE__ , __LINE__ , strerror( error ) );
		_exit( 1 );	// crash and burn
	}
	/*
	int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

	so we're calling  pthread create but gdcptr is of type struct gcd *, not void. So why is arg working?

	"The argument doesn't need to be cast"

	"the creating thread fills the struct and fills it, and just passes it to pthread_create"

	The pthread_create() function starts a new thread in the calling process.  The new thread starts
       execution by invoking start_routine(); arg is passed as the sole argument of start_routine().

	*/
	else if ( (error = pthread_join( tid, (void **)&rptr )) ){
		printf( "pthread_join() croaked in %s line %d: %s\n", __FILE__, __LINE__, strerror( error ) );
		_exit( 1 );	// crash and burn
	}
	/*
	int pthread_join(pthread_t thread, void **retval);

	"give me the address of another pointer (rptr) and i'll put the return contents of the thread into (rptr)"

  The  pthread_join()  function  waits  for  the thread specified by thread to terminate.  If that
       thread has already terminated, then pthread_join() returns immediately.  The thread specified by
       thread must be joinable.
	*/
	else{
		printf( "Joined thread returned GCD %d \n", *rptr );
		free( rptr );
		_exit( 0 );
		/*
			exit  - invokes a hidden stack of functions after the program is finished
			_exit  - ultimate kill switch to any program at any depth
			return  -
		 */
	}
}
