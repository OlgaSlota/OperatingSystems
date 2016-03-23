/*
 *author: Olga Slota
 */ 
 #include <sys/types.h>
 #include <sys/wait.h>
 #include <unistd.h>
 #include <time.h>
 #include <sys/times.h>
 #include <stdio.h>
 #include <stdlib.h>
#define N 7000
int glob = 0; 
int main (void){
clock_t clk1 =clock(); 
clock_t child;
clock_t sum =0;
time_t currentTime;
struct tms cpuTime;
pid_t pid;

for(int i=0 ; i<N ;i++){
    
if ( (pid = fork()) < 0)
printf("fork error");

else if (pid == 0) {
    child=clock();
    glob++;
    sum+= clock()-child;
    _exit(0);
} 
else{
    
    wait(0);
    
}}
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
printf("pid = %d, glob = %d \n", getpid() , glob);
return 0;
}