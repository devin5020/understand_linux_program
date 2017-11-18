/*************************************************************************
	> File Name: psh2.c
	> Author: Devin 
	> Mail: 
	> Created Time: Fri Nov 17 23:50:47 2017
    > Notes: shell using fork to execute command.
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>

#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>


#define MAXARGS 20
#define ARGLEN  100 

void SIGINT_handler(int);
int main()
{
    char * arglist[MAXARGS + 1];
    int numargs ;
    char argbuf[ARGLEN ];
    char * makestring(char *);
    int execute(char* arglist[]);

    numargs = 0;
   
    signal(SIGINT,SIGINT_handler); /*handle SIGINT signal*/

    while(numargs < MAXARGS){
        printf("Arg[%d]?",numargs);
        if(fgets(argbuf,ARGLEN,stdin)&& *argbuf != '\n')
            arglist[numargs++] = makestring(argbuf);
        else{
            if(numargs >0)
            {
                arglist[numargs]=NULL;
                

                execute(arglist);
                numargs = 0;
            }
        }
    }
   return 0;
}

int execute(char* arglist[])
{
    int pid,exitstatus;
    pid = fork();
    switch(pid){
        case -1:
           perror("fork failed");
           exit(1);
        case 0:
           execvp(arglist[0],arglist);
           perror("execvp failed");
           exit(1);
        default:
           while(wait(&exitstatus)!= pid)
              ;
           printf("child exited with status %d,%d\n",
                 exitstatus>>8, exitstatus&0x377);
  
    }

}

char* makestring(char * buf)
{
    char *cp  ;
    buf[strlen(buf)-1]='\0';
    cp = malloc(strlen(buf)+1);
    if(cp== NULL){
        fprintf(stderr,"no memory\n");
        exit(1);
    }
    strcpy(cp,buf);
    return cp;
}

void SIGINT_handler(int signum)
{
    ;
}
