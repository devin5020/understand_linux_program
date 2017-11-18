/*************************************************************************
	> File Name: who1.c
	> Author: 
	> Mail: 
	> Created Time: Sat 28 Oct 2017 05:55:24 PM CST
 ************************************************************************/

#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h> /*for exit function*/

#define SHOWHOST 
void show_info(struct utmp *utbufp);


int main()
{
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);

    if((utmpfd= open(UTMP_FILE,O_RDONLY))== -1)
    {
        perror(UTMP_FILE);
        exit(1);
    }
    while(read(utmpfd,&current_record,reclen)== reclen)
        show_info(&current_record);
    close(utmpfd);
}

void show_info(struct utmp *utbufp)
{
    printf("%-8.8s",utbufp->ut_name);
    printf(" ");


    printf("\n");
}
