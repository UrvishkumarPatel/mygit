#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

#define STRINGSIZE PATH_MAX
// # define GIT_PATH "git"
# define ROOT_PATH "."
// int remove(const char *pathname);
// On success, zero is returned.  On error, -1 is returned


// int unlink(const char *pathname);
// On success, zero is returned.  On error, -1 is returned
// int rmdir(const char *pathname);

// int stat(const char *pathname, struct stat *statbuf);


int is_dir(char* pathname){
	
	struct stat sb;
	if (stat(pathname, &sb) == -1){
		fprintf(stderr, "stat: cannot stat '%s': %s\n", pathname,strerror(errno));
		exit(EXIT_FAILURE);
	}
	return S_ISDIR(sb.st_mode);
}

void remove_file(char *file_name){
	if (unlink(file_name)==-1)
	{
		perror("rm");
	}
	// else{
	// 	printf("%sremoved\n", file_name);
	// }
	
}

void remove_dir(char *pathname) {
	DIR *dp;
	char dir_name[STRINGSIZE] = "";

	if ((dp = opendir(pathname)) == NULL){
		fprintf(stderr, "opendir: cannot opendir '%s': %s\n", pathname,strerror(errno));
		exit(EXIT_FAILURE);
	}

	struct dirent *d;
	while ((d = readdir(dp)) != NULL) {
		if(strcmp(d->d_name,".")==0) {
			strcpy(dir_name, pathname);
		}
		else if (strcmp(d->d_name,"..")!=0) {
			char path_string[STRINGSIZE] = "";
			strcpy(path_string, pathname);
			strcat(path_string,"/");
			strcat(path_string,d->d_name);
			if (is_dir(path_string)){
                // if (strcmp(d->d_name,".git") != 0 && strcmp(d->d_name, "git") != 0 ) //added
                if (strcmp(d->d_name, "git") != 0) //added			
				remove_dir(path_string);
			}
			else{
                if (strcmp(d->d_name,"a.out") != 0) //added
				remove_file(path_string);
			}
		}
	}

	if (rmdir(dir_name)==-1)		{
		perror("rm");
	}
	// else{
	// 	printf("%sremoved\n", dir_name);
	// }

	closedir(dp);

}


// int main(int argc, char *argv[])
// {	
// 	int rec = 0;
// 	for (int i = 1; i < argc; i++)
// 	{	
// 		if (strcmp(argv[i],"-r")==0)
// 		{
// 			rec = 1;
// 			// printf("%s\n", argv[i]);
// 		}
// 	}
// 	// printf("rec :%d\n", rec);

// 	if((argc-rec)==1){
// 		printf("(Syntax Error) Usage:%s [file]\n", argv[0]);
// 		return 0;
// 	}

// 	for (int i = 1; i < argc; i++)
// 	{
// 		if (strcmp(argv[i],"-r")!=0)
// 		{
// 			if (!is_dir(argv[i]))	{
// 				// printf("file\n");
// 				remove_file(argv[i]);
// 			} 
// 			else if (rec == 1) {
// 				// printf("folder\n");
// 				remove_dir(argv[i]);
// 			}
// 			else {
// 				printf("rm: %s, no such file\n", argv[i]);
// 			}		
// 		}


// 	}


// 	return 0;
// }
