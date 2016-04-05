/*
 Author:
 * Olga Slota
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int c; 
void handler (int signo) {
    
    if(signo == SIGUSR1){
        c += 1;
    }
    
    if(signo == SIGUSR2) {
        printf("\n\n");
        printf("Received [%d] signals.\nResending...\n", c);
       
        //READING PID OF SENDING PROGRAM :
        
        FILE *rfile;
        rfile = fopen("sendPID.txt", "r");
   
        if (!rfile)
        {
            printf("Unable to open file!");
            return ;
        }
    
        pid_t sendPID;
        char str[8];
        fread(&str,sizeof(char),8,rfile);
        fclose(rfile); 
        sendPID = atoi(str);
        
        //END OF READING
        
        for(int i = 0; i < c; i++) {
            kill(sendPID, SIGUSR1);
        }
        kill(sendPID, SIGUSR2);
        printf("Signals were sent.\n\n");
        exit(0);
    }
}

int digits (int n) {
   if (n < 10) return 1;
    return 1 + digits (n / 10);
}


int main(int argc, char** argv) {
   c = 0;
    
    //// SAVING PID TO FILE :
    FILE *wfile;
  
    wfile = fopen("listenPID.txt","w");
    if (!wfile)
    {
        printf("Unable to open file!");
        return 1;
    }
    pid_t listenPID = getpid();
    char str[8];

    sprintf(str, "%d", listenPID);
    fwrite(str, sizeof(char),digits(listenPID) , wfile);
    fclose(wfile);
    //END OF SAVING PID
    
    if(signal(SIGUSR1, handler) == SIG_ERR)
        printf("\n SignalError.\n");
    if(signal(SIGUSR2, handler) == SIG_ERR)
        printf("\n SignalError.\n");
    
    while(1) {    
    
    } 
    
    return (EXIT_SUCCESS);
}