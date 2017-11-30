/* spwd.c a simple version of pwd
 * 
 * */

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>/*exit function*/
#include<unistd.h>

#define BUFSIZE  256

#include <string.h>

void printpathto(ino_t this_inode);
void inum_to_name(ino_t inode_to_find, char * namebuf, int buflen);
ino_t get_inode(char * fname);

int main()
{
	printpathto(get_inode("."));   /* print path to here*/
	/* putchar('\n');                 /*then add new line*/

        printf("\n");
	return 0;
}

void printpathto(ino_t this_inode)
{
	ino_t my_inode;
	char its_name[BUFSIZE];
	if(get_inode("..") != this_inode)
	{
        chdir("..");
	
        inum_to_name (this_inode, its_name, BUFSIZE);
        my_inode = get_inode(".");
	printpathto(my_inode);
	printf("/%s", its_name);
	}

}


void inum_to_name(ino_t inode_to_find, char * namebuf, int buflen)
{
    DIR *dir_ptr;
	struct dirent * direntp;
	dir_ptr = opendir(".");
	if(dir_ptr == NULL){
	    perror(".");
		exit(1);
	}
    while ((direntp = readdir(dir_ptr)) != NULL)
		if(direntp -> d_ino == inode_to_find)
		{
			strncpy(namebuf, direntp->d_name, buflen);
			namebuf[buflen-1] = '\0'; /*just in case*/
			closedir(dir_ptr);
			return ;
		}
	fprintf(stderr,"error looking for lsinum %d\n", inode_to_find);
	exit(1);
}

ino_t get_inode(char * fname)
{
	struct stat info;
	if(stat(fname, &info) == -1)
	{
		fprintf(stderr,"cannot stat");
		perror(fname);
		exit(1);
	}
	return info.st_ino;

}


