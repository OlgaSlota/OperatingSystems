#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
int number;
int c;
pid_t listenPID;

void handler (int signo) {
    if(signo == SIGUSR1) {
        if(c == number) {
            kill(listenPID, SIGUSR2);
        }
        
        if(c < number) {
            c += 1;
            kill(listenPID, SIGUSR1);   
        }
    }
    if(signo == SIGUSR2){
        printf("\n\n");
        printf("Sent [%d] signals.\n\n", c);
        exit(0);
    }
}

int digits (int n) {
   if (n < 10) return 1;
    return 1 + digits (n / 10);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Please pass the number of signals you want to send.");
        return(0);
    }
    number = atoi(argv[1]);
    c = 0;
    
    //SAVIND PID OF SENDING PROGRAM :
    FILE *myfile;
    myfile = fopen("sendPID.txt","w");
    if (!myfile)
    {
        printf("Unable to open file!");
        return 1;
    }
    pid_t sendPID = getpid();
    char str1[10];

    sprintf(str1, "%d", sendPID);
    fwrite(str1, sizeof(char),digits(sendPID) , myfile);
    fclose(myfile);
    //END OF WRITING
    
    
   //READING PID OF LISTENING PROGRAM :
    FILE *readfile;
    readfile = fopen("listenPID.txt", "r");
   
    if (!readfile)
    {
        printf("Unable to open file!");
        return 1;
    }
    
    char str[10];
    fread(&str,sizeof(char),10,readfile);
    fclose(readfile); 
    listenPID= atoi(str);
    
    //END OF READING
    
    
    if(signal(SIGUSR1, handler) == SIG_ERR)
        printf("\n SignalError.\n");
    if(signal(SIGUSR2, handler) == SIG_ERR)
        printf("\n SignalError.\n");
    
    c += 1;
    kill(listenPID, SIGUSR1);
    
    
    while(1){
        
    }
    
    return (EXIT_SUCCESS);
}