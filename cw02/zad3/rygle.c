/*
 * author:
 *Slota Olga
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#define N 64

char filename[N];
int fd;
int menu()
{
        system("clear");
        int choice;
        printf("::::::::: WYBIERZ OPERACJE ::::::::::\n");
        printf("[1]. Ustaw rygiel na odczyt dla pliku\n");
        printf("[2]. Ustaw rygiel na zapis dla pliku\n");
        printf("[3]. Wyswietl liste zaryglowanych znakow pliku\n");
        printf("[4]. Zwolnij wybrany rygiel\n");
        printf("[5]. Odczytaj wybrany znak pliku\n");
        printf("[6]. Zmien wybrany znak pliku\n");
        printf("[7]. Wyjdz z programu\n");

        printf("Your choice: ");
        scanf("%d", & choice);
        return choice;
}
char read_position(int indeks)
{
        char z[1];
        lseek(fd, indeks, SEEK_SET);
        if( read(fd, z, 1) <= 0){
                printf("Couldn't read the sign\n");
                perror("");
        }
        lseek(fd, 0, SEEK_SET);
        return z[0];
}
void change(int indeks, char new)
{
        lseek(fd, indeks, SEEK_SET); 
        write(fd, &new, 1);
        lseek(fd, 0, SEEK_SET); 
}

void lockfile(off_t indeks, int typ)
{
    static struct flock lock;

    lock.l_type = typ;
    lock.l_start = indeks;
    lock.l_whence = SEEK_SET;
    lock.l_len = 1;
    lock.l_pid = getpid();

    int ret = fcntl(fd, F_SETLK, &lock);
    printf("Return value of fcntl: %d\n",ret);
    
}
void locked(){
     struct flock dane;
        dane.l_whence = SEEK_SET;
        dane.l_start = 0;
        dane.l_len = 1;
        dane.l_type = F_WRLCK;
        lseek(fd, 0, SEEK_SET);
        size_t length = lseek(fd, 0, SEEK_END) + 1;
         
   
    for(int i=1; i<length; i++) {
        if(fcntl(fd, F_GETLK, &dane) < 0) {
            printf("fctnl error\n");
        }

        if(dane.l_type != F_UNLCK)
            printf("PID:...%d     Byte:...%d    Type:...%s\n\n", dane.l_pid, dane.l_start,dane.l_type == F_WRLCK ? "write" : "read");
                        
        dane.l_start = i;
        dane.l_type = F_WRLCK;
    }
        }
   
int main(int argc, char *argv[])
{
        if( argc!=2 )
        {
                printf("Wrong arguments!\n");
                return 1;
        }
        strcpy(filename, argv[1]);

        fd = open( filename, O_RDWR );  
          if (!fd)
  {
    printf("Unable to open file!");
    return 1;
  }else{
        while(1)
        {
                int which;
                char new;
                int choice = menu();
                if( choice!=7 && choice!=3)
                {
                        printf("Number of byte: ");
                        scanf("%d", & which);
                }

                switch( choice )
                {
                        case 1:
                                lockfile(which, F_RDLCK);
                        break;
                        case 2:
                                lockfile(which, F_WRLCK);
                        break;
                        case 3:
                                locked();
                        break;
                        case 4:
                                lockfile(which, F_UNLCK);
                        break;

                        case 5:
                                printf("%c\n", read_position(which));
                        break;

                       case 6:
                                printf("New sign: ");
                                getchar(); 
                                new = getchar();
                                change(which, new);
                        break;
                        case 7:
                                close(fd);
                                return 0;
                }
               
                getchar();
                printf("Any key..\n");
                getchar();
        }
}}
