#include<bits/stdc++.h>
#define MAX_FILE_NAME_LENGTH 1024
using namespace std;
char** split_index_line(char* line_, string delimiter_){
    char delimiter[MAX_FILE_NAME_LENGTH];
    strcpy(delimiter, delimiter_.c_str());

    char** tokens= (char**)malloc(4*sizeof(char*));
    int k=0;

    char* token = strtok(line_, delimiter);
    while (token != NULL){
        tokens[k]= token;
        token = strtok(NULL, delimiter);
        k+=1;
    }
    tokens[k]=NULL;
    return tokens;  // check this
}
