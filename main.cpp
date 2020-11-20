/* same as the shell's main script
- parse the arguments
- fork (optional) the command and execute it
*/

#include "project_header.h"

int main(int argc, char* argv[]){

    if(argc==1){
		printf("No arguements given\n");
		exit(1);
	}
	else if(strcmp(argv[1],"init")==0){ init(argc,argv);}  //calling init
	else if(strcmp(argv[1],"add")==0){ add(argc,argv); } //calling add
	else if(strcmp(argv[1],"commit")==0){commit(argc,argv); } //calling commit
	else if(strcmp(argv[1],"branch")==0){branch(argc,argv); } //calling branch
	else if(strcmp(argv[1],"checkout")==0){checkout(argc,argv); } //calling checkout
	else if(strcmp(argv[1],"merge")==0){merge(argc,argv); } //calling merge
	else if(strcmp(argv[1],"log")==0){log(argc,argv); } //calling log
	else if(strcmp(argv[1],"reflog")==0){reflog(argc,argv); } //calling reflog
	else if(strcmp(argv[1],"reset")==0){reset(argc,argv); } //calling reset
	else if(strcmp(argv[1],"stash")==0){stash(argc,argv); } //calling stash

	// else if(strcmp(argv[1],"exit")==0) exit(1); //exiting the function
	cout<<"working fine: reaching end"<<endl;
    return 0;
}
