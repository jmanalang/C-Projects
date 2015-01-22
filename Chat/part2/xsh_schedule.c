#include <stdio.h>
#include <ctype.h>
#include <clock.h>
#include <thread.h>
/*each task and burn are represented as simple void methods that have a definite sleep method*/
int counter = 1;
void t1(void) {
	fprintf(stdout, "Task 1 running\n");
}

void t2(void) {
	fprintf(stdout, "Task 2 running\n");
}

void t3(void) {
	fprintf(stdout, "Task 3 running\n");
}

void burn(void) {
	fprintf(stdout, "Burn\n");
}
void framesize(void) {
	fprintf(stdout, "Frame: #%d\n", counter);
	counter = counter+1;
	sleep(5);
}
//This indicates the hyperperiod of the schedule
void hyperperiod(void) {
	fprintf(stdout, "Hyperperiod\n");
	sleep(5);
}

int start, end, total;
shellcmd xsh_schedule(int nargs, char * args[]) { 
 	//The ready create method creates the threads that runs a designated task 
 	start = clktime;
	ready(create((void *)t1, INITSTK, INITPRIO, "Task1_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t1, INITSTK, INITPRIO, "Task1_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t2, INITSTK, INITPRIO, "Task2_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t2, INITSTK, INITPRIO, "Task2_thread", 0), RESCHED_NO);
	sleep(500);
	framesize();
	ready(create((void *)t3, INITSTK, INITPRIO, "Task3_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t3, INITSTK, INITPRIO, "Task3_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t3, INITSTK, INITPRIO, "Task3_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t3, INITSTK, INITPRIO, "Task3_thread", 0), RESCHED_NO);
	sleep(500);
	framesize();
	ready(create((void *)t2, INITSTK, INITPRIO, "Task2_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t2, INITSTK, INITPRIO, "Task2_thread", 0), RESCHED_NO);
    	sleep(500);
	ready(create((void *)t1, INITSTK, INITPRIO, "Task1_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t1, INITSTK, INITPRIO, "Task1_thread", 0), RESCHED_NO);
	sleep(500);
	framesize();
	ready(create((void *)t3, INITSTK, INITPRIO, "Task3_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t3, INITSTK, INITPRIO, "Task3_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t3, INITSTK, INITPRIO, "Task3_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t3, INITSTK, INITPRIO, "Task3_thread", 0), RESCHED_NO);
	sleep(500);
	framesize();
	ready(create((void *)t2, INITSTK, INITPRIO, "Task2_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t2, INITSTK, INITPRIO, "Task2_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t1, INITSTK, INITPRIO, "Task1_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t1, INITSTK, INITPRIO, "Task1_thread", 0), RESCHED_NO);
	sleep(500);
	framesize();
	ready(create((void *)t2, INITSTK, INITPRIO, "Task2_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)t2, INITSTK, INITPRIO, "Task2_thread", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)burn, INITSTK, INITPRIO, "Burn", 0), RESCHED_NO);
	sleep(500);
	ready(create((void *)burn, INITSTK, INITPRIO, "Burn", 0), RESCHED_NO);
	sleep(500);
	framesize();
	hyperperiod();
	end = clktime;
	total = end - start;
	//Calculate the execution time
	fprintf(stdout, "Execution Time: %d\n", total);
	
	return 0;
     
}

