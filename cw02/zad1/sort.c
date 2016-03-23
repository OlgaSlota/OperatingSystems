#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h> 
#include <sys/resource.h>

int lib_sort(int length, char* name){
    int N;
    FILE *f;
    char comp[length]; // elements that are compared to our current x
    char x[length] ; // current element that we are placing   
    f=fopen(name,"r+");
    if (!f)
  {
    printf("Unable to open file!");
    return 1;
  }
     
    // counting number of records:
    fseek(f, 0, SEEK_END); 
    N = ftell(f)/length; // number of records
    fseek(f, 0, SEEK_SET);
      
    //sorting :
    for(int j=1 ; j<N ; j++ ){
        fseek(f, -(j+1)*length, SEEK_END );
        fread(&x,length,1,f); 
        fread(&comp,length, 1, f);
        
        fseek(f, -length, SEEK_CUR );
       
        while(ftell(f)< N*length && x[0] > comp[0]){
      
            fseek(f, -length , SEEK_CUR);
   
            fwrite(&comp,1, sizeof(char)*length, f);
             
            fseek(f, length , SEEK_CUR);
             
             if(ftell(f)<N*length){
                 fread(&comp,length, 1, f);
                 fseek(f, -length, SEEK_CUR );
             }else break;      
        }   
        fseek(f, -length , SEEK_CUR);
        fwrite(&x,1, sizeof(char)*length, f);
    }
    fclose(f); 
    return 0;
}

int sys_sort(int length, char* name){
    int file= open(name, O_CREAT | O_RDWR, S_IRUSR);
         
        if (!file)
        {
    printf("Unable to open file!");
    return 1;
        }
          char * y =malloc(sizeof(char)*length) ;
          char * cmp=malloc(sizeof(char)*length) ;
 
    int N = lseek(file, 0, SEEK_END)/length; // number of records
    lseek(file, 0, SEEK_SET);
      
    //sorting :
    for(int j=1 ; j<N ; j++ ){
        lseek(file, -(j+1)*length, SEEK_END );
        read(file,y, sizeof(char)*length); 
      
        read(file, cmp,length* sizeof(char));
        
        lseek(file, -length, SEEK_CUR );
       
        while(lseek(file, 0, SEEK_CUR)< N*length && y[0] > cmp[0]){
      
            lseek(file, -length , SEEK_CUR);
   
            write(file,cmp,length* sizeof(char));
             
            lseek(file, length , SEEK_CUR);
             
             if(lseek(file, 0, SEEK_CUR)<N*length){
                 read(file, cmp,length* sizeof(char));
                 lseek(file, -length, SEEK_CUR );
             }else break;      
        }   
        lseek(file, -length , SEEK_CUR);
        write(file, y,length* sizeof(char));
    }                    
        close(file);
        free(y);
        free(cmp);
        return 0;
}

int main(int argc, char** argv) {
    char * name = argv[1];
    char *type =  argv[3]; 
    int length = atoi(argv[2]);// length of record
    
    struct rusage usage;
    struct timeval u, u1;
    struct timeval s, s1;
    long micro , sec , sysmicro, syssec;
    
    if (strcmp(type,"lib")==0){
      
        getrusage(RUSAGE_SELF, &usage);
        u = usage.ru_utime;
        s= usage.ru_stime;
    
        lib_sort(length,name);
        getrusage(RUSAGE_SELF, &usage);
        u1 = usage.ru_utime;
        s1= usage.ru_stime;
   
        if(u1.tv_usec<u.tv_usec){
             micro = u.tv_usec-u1.tv_usec; 
            sec = u1.tv_sec-u.tv_sec -1;
        }
        else{
             micro =u1.tv_usec-u.tv_usec; 
            sec = u1.tv_sec-u.tv_sec ;
        }
       
     printf(" user time = %ld.%06ld\n", sec, micro);
     
      if(s1.tv_usec<s.tv_usec){
         sysmicro = s.tv_usec-s1.tv_usec; 
         syssec = s1.tv_sec-s.tv_sec -1;
      }
      else{ 
         sysmicro =s1.tv_usec-s.tv_usec; 
         syssec = s1.tv_sec-s.tv_sec ;
      }     
     printf(" sys time = %ld.%06ld\n\n", syssec,sysmicro);
    }
    if (strcmp(type,"sys")==0){
        
      getrusage(RUSAGE_SELF, &usage);
     u = usage.ru_utime;
     s= usage.ru_stime;
     
       sys_sort(length,name);
       
      getrusage(RUSAGE_SELF, &usage);
     u1 = usage.ru_utime;
     s1= usage.ru_stime;
      
         if(u1.tv_usec<u.tv_usec){
         micro = u.tv_usec-u1.tv_usec; 
         sec = u1.tv_sec-u.tv_sec -1;
      }
      else{
         micro =u1.tv_usec-u.tv_usec; 
         sec = u1.tv_sec-u.tv_sec ;
      }
     printf(" user time = %ld.%06ld\n", sec, micro);
     
      if(s1.tv_usec<s.tv_usec){
         sysmicro = s.tv_usec-s1.tv_usec; 
         syssec = s1.tv_sec-s.tv_sec -1;
      }
      else{
         sysmicro =s1.tv_usec-s.tv_usec; 
         syssec = s1.tv_sec-s.tv_sec ;
      }     
     printf(" sys time = %ld.%06ld\n\n", syssec,sysmicro);

    }

    if (strcmp(type,"sys")!=0 &&  (strcmp(type,"lib")!=0)) {
        printf("Wrong argument! Choose sys or lib. ");
    }    
    return 0;
    
}