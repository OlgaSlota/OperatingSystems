/* 
 * File:   main.c
 * Author: Słota Olga
 */
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "liblist.h"
#include <time.h>
#include <sys/time.h> 
#include <sys/resource.h>

struct rusage usage;
clock_t my_clk[4];

struct timeval user[4];
struct timeval sys[4];

void ctrl_time(int n){
     getrusage(RUSAGE_SELF, &usage);
       my_clk[n] = clock();
       user[n] = usage.ru_utime;
       sys[n] = usage.ru_stime;
       printf("Control point %d\n\n real time = %.6ld\n", n,my_clk[n]/CLOCKS_PER_SEC);
       printf(" user time = %ld.%06ld\n", user[n].tv_sec, user[n].tv_usec);
       printf(" sys time = %ld.%06ld\n\n", sys[n].tv_sec,sys[n].tv_usec);
       if(n>0){
           printf("real time : now-begin =%.6ld\n", (my_clk[n]-my_clk[0])/CLOCKS_PER_SEC);
           printf("user time : now-begin = %ld.%06ld\n", user[n].tv_sec- user[0].tv_sec, user[n].tv_usec-user[0].tv_usec);
           printf(" sys time : now-begin = %ld.%06ld\n\n", sys[n].tv_sec- sys[0].tv_sec, sys[n].tv_usec-sys[0].tv_usec);
       }
       if(n>1){
           printf("real time : now-previous =%.6ld\n", (my_clk[n]-my_clk[n-1])/CLOCKS_PER_SEC);
           printf("user time : now-previous = %ld.%06ld\n", user[n].tv_sec- user[n-1].tv_sec, user[n].tv_usec-user[n-1].tv_usec);
           printf(" sys time : now-previous = %ld.%06ld\n\n", sys[n].tv_sec- sys[n-1].tv_sec, sys[n].tv_usec-sys[n-1].tv_usec);           
       }
       printf("/*************************************************************************************************************/\n");
}


int main(int argc, char *argv[]){
   
        srand(time(NULL));
        int r1,r2,r3,r4,r5,r6;
        
        ctrl_time(0);
        
        char a[10][10]={"Ola", "Ala", "Iza", "Bogdan" , "Bartek" , "Piotr" , "Aga" ,"Tomek", "Olga", "Marta"};
        char b[10][10]= {"Kowalski", "Nowak" ,"Saski" , "Polski" , "Skalski" , "Rus","Solny" , "Slota", "Wolny" , "Darski"};
        char c[10][10]= {"2.11.1939", "14.5.1965" ,"1.2.2000", "2.4.1970", "4.6.1980","2.4.1978","2.4.1966", "3.6.1999","14.5.1975","14.5.1968"};
        char d[10][40]= {"ab@google.com", "cd@onet.pl", "ab@google.com","a12@google.com","adlkjg@google.com", "agh@poczta.pl","abcdefg@google.com","12345@google.com","15@google.com","al@google.com"};
        char e[10][40]= {"Krakow" , "Poland","London","Moscow" , "Paris" , "Rome" , "Brasil" , "Warsaw", "Lyon","Poznan"};
        char f[10][10]={"123456", "098765","89374390","2345765", "78453853", "4729424","867943","6876352","326453","23435"};
        
        for ( int k = 0 ; k< 30 ; k++){
            
        node * lista = create_list();
        
        for(int j = 0 ; j< 100000 ; j++){
            r1 = rand() % 10;
            r2 = rand() % 10;
            r3 = rand() % 10;
            r4 = rand() % 10;
            r5 = rand() % 10;
            r6 = rand() % 10;
            person * per = create_person(a[r1], b[r2] ,c[r3] , d[r4] , f[r5], e[r6]);
            insert(&lista,per);
        }
        
        for ( int i=0 ; i<100 ; i++){ 
            search(lista,"Ola", "Wolny");
           
        }
        mergeSort(lista);
        destroy(&lista);
        if(k==10)
            ctrl_time(1);
        if(k==20)
            ctrl_time(2);
        }
       
       // print(lista);
       //  clock_t stop = clock();
       // printf(" times : %ld  "  ,(stop - start) / CLOCKS_PER_SEC);
      //  printf(" start : %ld  "  ,start);
     //   printf(" stop : %ld  "  ,stop);
        // destroy(&lista);
      
        ctrl_time(3);


	return 0;
}