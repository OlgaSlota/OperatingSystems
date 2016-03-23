/* 
 * Author: Slota Olga
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <sys/types.h>
#include <linux/sched.h>
#include <stdlib.h>
#include <unistd.h>
 #include <time.h>
 #include <sys/times.h>
#include <linux/sched.h>

#define N 150000
#define SIZE 4096
int glob = 0; 
clock_t clk1; 
clock_t child;
clock_t sum =0;
struct tms cpuTime;

int fun(void * args) {
    child=clock();
    times(&cpuTime);
    glob++;
    sum+= clock()-child;
    _exit(0);
}
int main() {
    
    clock_t clk1 =clock(); 
    
    void * base = malloc((N+1)*SIZE);
 
    void * stack = (void *)(base);

    for (int i = 0; i < N; i++) { 
        clone(&fun, stack+((i+1)*SIZE), 0 ,0);
        wait();
    }
     if (times(&cpuTime) < 0)         /* Get process times.       */
           perror("times error");
        else {
           printf("Parent process user time = %f\n",
                ((double) cpuTime.tms_utime)/CLOCKS_PER_SEC);
           printf("Parent process system time = %f\n",
                ((double) cpuTime.tms_stime)/CLOCKS_PER_SEC);
           printf("Child process user time = %f\n",
                ((double) cpuTime.tms_cutime)/CLOCKS_PER_SEC);
           printf("Child process system time = %f\n",
                ((double) cpuTime.tms_cstime)/CLOCKS_PER_SEC);
        }
    printf("Parent process real time = %ld clock ticks\n",(clock()-clk1));
    printf("Child process real time = %ld clock ticks \n",sum);
    printf( "after threads %d\n", glob);
    return 0;
}