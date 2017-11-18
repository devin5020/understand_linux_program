/*************************************************************************
	> File Name: waitdemo1.c
	> Author: 
	> Mail: 
	> Created Time: Sat Nov 18 09:51:25 2017
    > shows how parents wait for child process end.
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


#define DELAY 2

int main()
{
    int newpid;
    void child_code(),paraent_code();
    printf("Before :mypid is %d\n",getpid);
    if((newpid = fork()) == -1)
        perror("fork");
    else if(newpid == 0)
        child_code(DELAY);
    else 
        paraent_code(newpid);


    return 0;
}

void child_code(int delay)
{
    printf("child %d here. will sleep for %d seconds\n",getpid,delay);
    sleep(delay);
    printf("child done. about to exit\n");
    exit(17);
}


void paraent_code(int childpid)
{
    int wait_rv;
    wait_rv = wait(NULL);
    printf("done waiting for %d. Wait Returned: %d\n",childpid, wait_rv);
}
