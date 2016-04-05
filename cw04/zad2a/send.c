/*
 * Author:
 * Olga Slota
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
int N; // initial number of signals to send
int c; // counter of signals received

void handler (int signo) {
    if(signo == SIGUSR1) {
       c += 1;
    }
    if(signo == SIGUSR2){
        printf("\nSent : [%d] signals, received back: [%d]!\n\n", N, c);
        exit(0);
    }
}

int digits (int n) {
   if (n < 10) return 1;
    return 1 + digits (n / 10);
}

int main(int argc, char** argv) {
    
    
    if (argc != 2) {
        printf("Please pass the number of signals to send.");
        return(0);
    }
    
    
    N = atoi(argv[1]);
    c = 0;
    
    // SAVING PID TO FILE :
    
    FILE *myfile;
    myfile = fopen("sendPID.txt","w");
    if (!myfile)
    {
        printf("Unable to open file!");
        return 1;
    }
    pid_t sendPID = getpid();
    char str1[8];

    sprintf(str1, "%d", sendPID);
    fwrite(str1, sizeof(char),digits(sendPID) , myfile);
    fclose(myfile);
    
    //END OF SAVING PID
    
    
    //READING PID OF LISTENING PROGRAM :
    
    FILE *readfile;
    readfile = fopen("listenPID.txt", "r");
   
    if (!readfile)
    {
        printf("Unable to open file!");
        return 1;
    }
    
    pid_t listenPID;
    char str[8];
    fread(&str,sizeof(char),8,readfile);
    fclose(readfile); 
    listenPID= atoi(str);
    
    //END OF READING
    
    
    if(signal(SIGUSR1, handler) == SIG_ERR)
        printf("\n SignalError.\n");
    if(signal(SIGUSR2, handler) == SIG_ERR)
        printf("\n SignalError.\n");
    
    
    for(int i = 0; i < N; i++){
        kill(listenPID, SIGUSR1);
    }
    kill(listenPID, SIGUSR2);
    
    while(1){
        //waiting for response
    }
    
    return (EXIT_SUCCESS);
}