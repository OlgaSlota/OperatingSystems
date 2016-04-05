/*
 Author: 
 * Olga Slota
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int N; 
int repeat; 
int flag; //if true -> we increment repetitions

char * reverse (char * s) {
    int length = strlen(s);
    int halfALength = length/2;
    char temp;
    char * reversed = (char *)malloc(length * sizeof(char));
    strcpy(reversed, s);
    int i = 0;
    int k = 0;
    
    for(i = 0, k = (length - 1); i < halfALength; i++,k--)
    {
        temp = reversed[k];
        reversed[k] = reversed[i];
        reversed[i] = temp;
    }
    return reversed;
}

void handler (int signo) {
    
    if(signo == SIGINT){
        printf("Received SIGINT.\n");
        exit(0);
    }
    
    if(signo == SIGTSTP) {
        if(repeat == N && flag == 1) {
            flag = 0;
            repeat = N - 1;
            return;
        }
        
        if(repeat == 0 && flag == 0) {
            flag = 1;
            repeat = 1;
            return;
        }
        
        if(repeat < N && flag == 1){
            repeat += 1;
            return;
        }
        
        if(repeat > 0 && flag == 0) {
            repeat -= 1;
            return;
        }     
    }
}


int main(int argc, char** argv) {
    
   
    if(signal(SIGINT, handler) == SIG_ERR)
        printf("\n SignalError.\n");
    
    
    struct sigaction action;
    action.sa_flags = NULL;
    sigfillset(&action.sa_mask);
    action.sa_sigaction = handler;
    sigaction(SIGTSTP, &action, NULL);
    
    if (argc != 3) {
        printf("Wrong args! Please pass the text to print and number of repetitions.");
        return(0);
    }
    
    char * string = argv[1];
    N = (3 * atoi(argv[2])) - 1;
    repeat = 0;
    flag = 1;
    
    char * rev = reverse(string);
        
    while(1){
        
        if(repeat % 3 == 1) {
            for(int i = 0; i < repeat/3; i++){
                printf("%s ", reverse(string));
            }
            printf("%s\n", reverse(string));
        }
        
        else {
            for(int i = 0; i < repeat/3; i++){
                printf("%s ", string);
            }
            printf("%s\n", string);
        }
    }
    return (EXIT_SUCCESS);
}
