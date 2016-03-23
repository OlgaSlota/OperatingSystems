#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <ftw.h>
#include <errno.h>
#include <stdio.h>
 
#if MAX < 1
#define MAX 20
#endif

char modes[10];
    
static int file_info(FILE *const f, const char *path, const struct stat *info,
                         struct tm *localmtime)
{
    struct stat st;
    char * m = (char*)malloc(11 * sizeof(char));
    stat(path, &st);
     (S_ISDIR(st.st_mode)) ? strcpy(m, "d") : strcpy(m, "-");
    (st.st_mode & S_IRUSR) ? strcat(m, "r") : strcat(m, "-");
    (st.st_mode & S_IWUSR) ? strcat(m, "w") : strcat(m, "-");
    (st.st_mode & S_IXUSR) ? strcat(m, "x") : strcat(m, "-");
    (st.st_mode & S_IRGRP) ? strcat(m, "r") : strcat(m, "-");
    (st.st_mode & S_IWGRP) ? strcat(m, "w") : strcat(m, "-");
    (st.st_mode & S_IXGRP) ? strcat(m, "x") : strcat(m, "-");
    (st.st_mode & S_IROTH) ? strcat(m, "r") : strcat(m, "-");
    (st.st_mode & S_IWOTH) ? strcat(m, "w") : strcat(m, "-");
    (st.st_mode & S_IXOTH) ? strcat(m, "x") : strcat(m, "-");
    
    if(strcmp(m, modes)== 0)
    {
        printf("%s\n %s  SIZE: %.0f B, LAST ACCESS: %04d-%02d-%02d %02d:%02d:%02d.  \n",
            path, m,(double)info->st_size, localmtime->tm_year + 1900, localmtime->tm_mon + 1, 
            localmtime->tm_mday, localmtime->tm_hour, localmtime->tm_min, localmtime->tm_sec);
    }
    return 0;
}
static int check_file(const char *path, const struct stat *info,
                    int typeflag, struct FTW *ftwinfo)
{   struct tm atime;
    FILE *f;
  
    if (typeflag == FTW_F) {
        localtime_r(&(info->st_atime), &atime);
        file_info(f, path, info, &atime); 
        return 0;
    }
    return 0;
}
  
int main(int argc, char** argv)
{
    
    if(argc != 3) {
        printf("Wrong arguments.\n");
        return 0; 
    }
    
    char * init= argv[1];
    char * access= argv[2];
    
    for ( int i=0; i<10 ; i++)
        modes[i] = access[i]; 
        
    if (nftw(init, check_file, MAX, FTW_CHDIR)) {
        fprintf(stderr, "Failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}