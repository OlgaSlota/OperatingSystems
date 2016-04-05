#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int c;
pid_t sendPID;

void handler (int signo) {
    
    if(signo == SIGUSR1){
        
        if(c != 0) 
        {
            c += 1;
            kill(sendPID,SIGUSR1);
        }
        
        if(c == 0) {
            //READING PID OF SENDING PROGRAM :
            FILE *readfile;
            readfile = fopen("sendPID.txt", "r");
   
            if (!readfile)
            {
                printf("Unable to open file!");
                return 1;
            }
            char str[10];
            fread(&str,sizeof(char),10,readfile);
            fclose(readfile); 
            sendPID = atoi(str);
            //END OF READING
        
            c += 1;
            kill(sendPID,SIGUSR1);
        }
              
    }
    
    if(signo == SIGUSR2) {
        printf("\n\nReceived [%d] SIGUSR1 signals .\n\n", c);
        kill(sendPID, SIGUSR2);
        
        exit(0);
    }
}

int digits (int n) {
   if (n < 10) return 1;
    return 1 + digits (n / 10);
}

int main(int argc, char** argv) {
    c = 0;
    
    //SAVING PID TO FILE :
    FILE *myfile;
  
    myfile = fopen("listenPID.txt","w");
    if (!myfile)
    {
        printf("Unable to open file!");
        return 1;
    }
    pid_t listenPID = getpid();
    char str[10];

    sprintf(str, "%d", listenPID);
    fwrite(str, sizeof(char),digits(listenPID) , myfile);
    fclose(myfile);
    //END OF WRITING
    
    if(signal(SIGUSR1, handler) == SIG_ERR)
        printf("\n SignalError.\n");
    if(signal(SIGUSR2, handler) == SIG_ERR)
        printf("\n SignalError.\n");
    
    while(1) {    
    
    } 
    
    return (EXIT_SUCCESS);
}