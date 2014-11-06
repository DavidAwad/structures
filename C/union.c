#include <stdio.h>
#include <stdlib.h>
#include <string.h>


union foo {
  int a;   // can't use both a and b at once
  char b;
} foo;

struct bar {
  int a;   // can use both a and b simultaneously
  char b;
} bar;

int main(){





union foo x;
x.a = 3; // OK

printf("x.a is now %d \n",x.a);

x.b = 'c'; // NO! this affects the value of x.a!



struct bar y;
y.a = 3; // OK
y.b = 'c'; // OK


printf("%i, %i \n", x.a, x.b);

printf("%d \n" , x.a);

puts("here is a print statement"); 




/*   



With a union, you're only supposed to use one of the elements, because they're all stored at the same spot. This makes it useful when you want to store something that could be one of several types. A struct, on the other hand, has a separate memory location for each of its elements and they all can be used at once.

To give a concrete example of their use, I was working on a Scheme interpreter a little while ago and I was essentially overlaying the Scheme data types onto the C data types. This involved storing in a struct an enum indicating the type of value and a union to store that value.


If you're wondering what setting x.b to 'c' changes the value of x.a to, technically speaking it's undefined. On most modern machines a char is 1 byte and an int is 4 bytes, so giving x.b the value 'c' also gives the first byte of x.a that same value:


Why are the two values the same? Because the last 3 bytes of the int 3 are all zero, so it's also read as 99. If we put in a larger number for x.a, you'll see that this is not always the case:



 */

}
