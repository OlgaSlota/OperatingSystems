/* 
 * Author: Slota Olga
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>


int files = 0;
int sum = 0;
int children = 0;

int main(int argc, char * argv[])
{
char * path;
char * v;
char * w;
        
path = argv[1];

if(argv[2])
v = argv[2];
if(argv[3])
w = argv[3];

if(!v)
    strcpy(v,"emtpy");
if(!w)
    strcpy(w,"emtpy");
       
if(path == NULL)
{
    path = (char *)malloc(sizeof(char) * 2);
    strcpy(path, "../..");
}
if(strcmp(v, "-v") == 0)
printf("Current directory : %s\n", path);

DIR * dir;
dir = opendir(path);
int error_code = errno;

if(dir == NULL)
{   printf("Error while opening directory.\n");
    exit(error_code);
}

struct dirent * d;

pid_t PID;
char tmp[512];

while((d = readdir(dir)) != NULL)
{
    if(strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0)
    {
        strcpy(tmp, path);
        strcat(tmp, "/");
        strcat(tmp, d->d_name); 
			
       struct stat s;
        if(stat(tmp, &s) < 0)
        fprintf(stderr, "stat error\n");

        if(S_ISDIR(s.st_mode))
	{   children++;
            PID = vfork();

            if(strcmp(w, "-w") == 0){
                sleep(5);
            } 
            if(PID == -1)
            {	children--;
		printf( "Fork errror\n");
		exit(2);
		
            }
	
            else
                if(PID == 0)
		{   char *args[] = {"main", tmp, v,w, "/", 0}; 
                    char *env[] = { 0 };
					
                    if(strcmp(v, "-v") == 0)
                    {   if(execve("main", args, env) < 0)
			printf( "execve error\n");
                    }
                    else
			if(execve("main", args, env) < 0)
			printf( "execve error\n");
		}
	}	
        else 
	if(S_ISREG(s.st_mode))
            files++;
         }
}

sum+= files ;       
printf("Number of files:%d,   PID:%d\n", sum, getpid());
while(children--)
{
    wait();
}
  _exit(sum+files);        
}
