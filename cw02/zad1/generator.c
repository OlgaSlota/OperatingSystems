/* 
 * Author: Slota Olga
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char** argv) {
     int SIZE = atoi(argv[2]);
    int N = atoi(argv[3]);
    FILE *ptr_myfile;
    char records[SIZE] ;

    srand(time(NULL));
    
    ptr_myfile=fopen(argv[1],"w");
    if (!ptr_myfile)
{
    printf("Unable to open file!");
    return 1;
}
    for ( int i =0 ; i<N; i++)
        for(int j = 0 ; j<SIZE ; j++)
{
    records[j]= '!'+(rand()%93);
    
    fwrite(&records[j],1, sizeof(char), ptr_myfile);
}
    fclose(ptr_myfile);
    return 0;
    
}
