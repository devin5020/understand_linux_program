/*************************************************************************
	> File Name: listchars.c list individually all the chars on input
    > output : char and ascii code, onw pair per line
    > input : stdin ,until on 'Q'
    > notes  : useful tro show that  buffering and editing exits
	> Author: 
	> Mail: 
	> Created Time: Sat 02 Dec 2017 10:40:01 AM CST
 ************************************************************************/

#include<stdio.h>

int main()
{
    int c ,n ;
    while( (c = getchar()) != 'Q')
        printf("char %3d is %c code %d\n", n++, c, c);

    return 0;
}

