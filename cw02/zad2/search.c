/* 
 * Author: Olga Slota
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

void dir_info(char * path, char * modes, char * relative) {
    DIR *d;
    struct dirent *dir;
    if ((d = opendir(path)) == NULL) {
        perror ("Wrong path, couldn't open...");
        exit (1);
    }
    
        while ((dir = readdir(d)))
        {
            char * name = dir->d_name;
            char * path2 = (char*)malloc(2 + strlen(path) + strlen(name));
            char * relative2 = (char*)malloc(2 + strlen(path) + strlen(name));
            strcpy(path2, path);
            strcat(path2, name);
            strcpy(relative2, relative);
            strcat(relative2, name);
            
            if((int)dir->d_type == 4) {
                if( (strcmp(name, "..")!=0) && (strcmp(name, ".") != 0) ) {
                    strcat(path2, "/");
                    strcat(relative2, "/");
                    dir_info(path2, modes, relative2);
                    free(path2);
                    free(relative2);
                }   
            }  
            if((int)dir->d_type == 8) {
                file_info(path2, modes, relative2);
                
            }
    }
    closedir(d);
}
void file_info(char * f, char * modes, char * path) {
    struct stat st;
    stat(f, &st);
    char * m = (char*)malloc(11 * sizeof(char));
    
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
    
    if(strcmp(modes, m)==0) {
        char * date;
        time_t * t;
        t = &st.st_atime;
        date = ctime(t);
        printf("%s, SIZE: %ld B, LAST ACCESS: %s, Permissions: %s\n ", path, st.st_size ,date, m );
    }
    
}
int main(int argc, char** argv) {    
    
    if(argc!=3) {
        printf("Wrong arguments.\n");
        return 0; 
    }
    char * path;
    char * access;
    char * relative = "/";
    path = argv[1];
    access = argv[2];
    dir_info(path, access, relative);
    return(0);
}