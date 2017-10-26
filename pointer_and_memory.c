#include <stdio.h>
void main(){
	int a=1;
	int b=2;
	int *pa=&a; //pa means pointer of variable a
	int *pb=&b; //pb means pointer of variable b
	printf("a ma is: %08x and  b ma is: %08x",pa,pb);//i'd like to print out the memory address, seems not easy
	// the result is a ma is: 03748b9c and  b ma is: 03748b98, different as gdb side, but the values seems right
}
/*
(gdb) start
Temporary breakpoint 1 at 0x400538: file pointer_and_memory.c, line 3.
Starting program: /root/learning_c/./a.out 

Temporary breakpoint 1, main () at pointer_and_memory.c:3
3		int a=1;
(gdb) print a
$1 = 0
(gdb) n
4		int b=2;
(gdb) print a
$2 = 1
(gdb) n
5		int *pa=&a;
(gdb) print a
$3 = 1
(gdb) print pa
$4 = (int *) 0x0
(gdb) n
6		int *pb=&b;
(gdb) print pa
$5 = (int *) 0x7fffffffe51c   // strange here, as i understand, pb should be lower than pa by 4 bytes, but the result is contract, pa is e51c and pb is e518
(gdb) n
7		printf("a ma is: %d and  b ma is: %d",pa,pb);
(gdb) print pb
$6 = (int *) 0x7fffffffe518

 */
