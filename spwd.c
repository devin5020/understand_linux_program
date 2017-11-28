/* spwd.c a simple version of pwd
 * 
 * */

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>

#define BUFSIZE  1024

void printpathto(ino_t this_inode);
void inum_to_name(ino_t inode_to_find, char * namebuf, itn buflen);
ino_t get_inode(char * fname);

int main()
{
	printpathto(get_inode("."));   /* print path to here*/
	putchar("\n");                 /*then add new line*/

	return 0;
}

void printpathto(ino_t this_inode)
{
	ino_t my_inode;
	char its_name[BUFSIZE];
	if(get_inode(this_node, its_name, BUFSIZE) != this_inode)
	{
	my_inode = get_inode(".");
	printpathto(my_inode);
	printf("%s\n", its_name);
	}

}


void inum_to_name(ino_t inode_to_find, char * namebuf, itn buflen)
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
			strcpy(namebuf, direntp -> d_name, buflen);
			namebuf[buflen-1] = '\0'; /*just in case*/
			closedir(dir_ptr);
			return ;
		}
	fprintf(stderr,"error looking for inum %d\n", inode_to_find);
	exit(1);
}

ino_t get_inode(char * fname)
{
	struct stat_info;
	if(stat(fname, &info) == -1)
	{
		fprintf(stderr,"cannot stat");
		perror(fname);
		exit(1);
	}
	return info.st_ino;

}


