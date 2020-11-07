#include<bits/stdc++.h>
#define MAX_FILE_NAME_LENGTH 1024
#define TOKEN_NOS 10
using namespace std;
int DEFAULT;

// char** split_index_line(char* line_, string delimiter_){
//     char delimiter[MAX_FILE_NAME_LENGTH];
//     strcpy(delimiter, delimiter_.c_str());

//     char** tokens= (char**)malloc((100)*sizeof(char*));
//     int k=0;

//     char* token = strtok(line_, delimiter);
//     while (token != NULL){
//         tokens[k]= token;
//         token = strtok(NULL, delimiter);
//         k+=1;
//     }
//     tokens[k]=NULL;
//     return tokens;  // check this
// }

char** split_index_line(char * line_, string delimiter_,  int * n=&DEFAULT){
	// https://www.man7.org/linux/man-pages/man3/strsep.3.html
	// char *strsep(char **stringp, const char *delim);
    char delimiter[MAX_FILE_NAME_LENGTH];
    strcpy(delimiter, delimiter_.c_str());
	int tok_nos = TOKEN_NOS;
	char **args = (char**)malloc(tok_nos * sizeof(char*));
	int i = 0;
	while(1){
		if (i>=tok_nos)
		{
			tok_nos+=TOKEN_NOS;
			args = (char**)realloc(args, sizeof(char*)*tok_nos);
		}

		args[i] = strsep(&line_ , delimiter);

		if (args[i]==NULL) break;
		if (strlen(args[i])==0) {
			i--;
		}

		i++;
	}
	// printf("tok_nos : %d\n", tok_nos)

	// printf("no. of args: %d\n", i);
	*n = i;
	return args;
}