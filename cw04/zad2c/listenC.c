/*
 Author:
 * Olga Slota
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int c;
int RECEIVING;
void handlerOne (int signo) {
    c += 1;
}
void handlerTwo(int signo) {
        printf("\n\nReceived [%d] signals.\nResending..", c);
        RECEIVING = 0;  
}

int digits (int n) {
   if (n < 10) return 1;
    return 1 + digits (n / 10);
}

int main(int argc, char** argv) {
    c = 0;
    RECEIVING = 1;
    
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
    
    struct sigaction first_action, second_action;
    first_action.sa_sigaction = &handlerOne;
    first_action.sa_flags = SA_SIGINFO;

    if(sigaction((SIGRTMIN + 1), &first_action, NULL) < 0) {
        fputs("An error occured while setting SIGUSR2 signal handler.\n", stderr);
        return EXIT_FAILURE;
    }
    
    second_action.sa_sigaction = &handlerTwo;
    second_action.sa_flags = SA_SIGINFO;
    
    if(sigaction((SIGRTMIN + 2), &second_action, NULL) < 0) {
        fputs("An error  while setting SIGUSR2 signal handler.\n", stderr);
        return EXIT_FAILURE;
    }
    
   
    while(RECEIVING) {    
        pause();  
    } 
    
    //READING PID OF SENDING PROGRAM :
        
        FILE *rfile;
        rfile = fopen("sendPID.txt", "r");
   
        if (!rfile)
        {
            printf("Unable to open file!");
            return 1;
        }
    
        pid_t sendPID;
        char s[8];
        fread(&s,sizeof(char),8,rfile);
        fclose(rfile); 
        sendPID = atoi(s);
        
        //END OF READING
        
        union sigval value;
        
        for(int i = 0; i < c; i++) {
            if(sigqueue(sendPID, (SIGRTMIN + 1), value) < 0) {
            fputs("Kill error", stderr);
            exit(EXIT_FAILURE);
            }
        }
        
        if(sigqueue(sendPID, (SIGRTMIN + 2), value) < 0) {
            fputs("Kill error", stderr);
            exit(EXIT_FAILURE);
        }
        printf(" Signals were sent.\n\n");
        exit(0);
    
    return (EXIT_SUCCESS);
}