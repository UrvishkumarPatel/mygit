/* same as the shell's main script
- parse the arguments
- fork (optional) the command and execute it
*/

#include "object.h"
#include "init.h"
#include <string>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

//test hash_object
int main(int argc, char* argv[]){
    // string file_name=argv[1];
    // cout<<file_name<<endl;
    // add_run(file_name);
    if(argc==1){
		printf("No arguements given\n");
		exit(1);
	}
	else if(strcmp(argv[1],"init")==0){ init(argc,argv);}  //calling ls
	else if(strcmp(argv[1],"add")==0){ add(argc,argv); } //calling wgrep
	else if(strcmp(argv[1],"commit")==0){commit(argc,argv); } //calling wcat
	else if(strcmp(argv[1],"exit")==0) exit(1); //exiting the function
    return 0;
}