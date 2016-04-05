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
int number;
int c;

void Firsthandler (int signo) { 
    c += 1;
}
void Secondhandler(int signo) { 
    printf("\n\nSent [%d] signals received back [%d]!\n\n", number, c);
    exit(0);
}

int digits (int n) {
   if (n < 10) return 1;
    return 1 + digits (n / 10);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("You have to pass how many signals you want to send.");
        return(0);
    }
    number = atoi(argv[1]);
    c = 0;
    pid_t sendPID; 
    pid_t listenPID;
    
    ////// SAVING PID TO FILE :
    FILE *wfile;
    wfile = fopen("sendPID.txt","w");
    if (!wfile)
    {
        printf("Unable to open file!");
        return 1;
    }
    sendPID = getpid();
    char str1[8];

    sprintf(str1, "%d", sendPID);
    fwrite(str1, sizeof(char),digits(sendPID) , wfile);
    fclose(wfile);

    // END OF WRITING
    
    //READING PID OF SENDING PROGRAM :
    FILE *rfile;
    rfile = fopen("listenPID.txt", "r");
   
    if (!rfile)
    {
        printf("Unable to open file!");
        return 1;
    }
    
    char str[8];
    fread(&str,sizeof(char),8,rfile);
    fclose(rfile); 
    listenPID= atoi(str);
    //END OF READING
    
    struct sigaction first_action, second_action;
    first_action.sa_sigaction = &Firsthandler;
    first_action.sa_flags = SA_SIGINFO;

    if(sigaction((SIGRTMIN + 1), &first_action, NULL) < 0) {
        fputs("An error occured while setting SIGUSR2 signal handler.\n", stderr);
        return EXIT_FAILURE;
    }
    
    second_action.sa_sigaction = &Secondhandler;
    second_action.sa_flags = SA_SIGINFO;
    
    if(sigaction((SIGRTMIN + 2), &second_action, NULL) < 0) {
        fputs("An error occured while setting SIGUSR2 signal handler.\n", stderr);
        return EXIT_FAILURE;
    }
    
    union sigval value;
    
    for(int i = 0; i < number; i++){
        if(sigqueue(listenPID, (SIGRTMIN + 1), value) < 0) {
            fputs("Sigqueue error", stderr);
            exit(EXIT_FAILURE);
        }
    }
     
    if(sigqueue(listenPID, (SIGRTMIN + 2), value) < 0) {
            fputs("Sigqueue error", stderr);
            exit(EXIT_FAILURE);
        }
    
    while(1){
        pause();
    }
    
    return (EXIT_SUCCESS);
}
