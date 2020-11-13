

void log(int argc, char* argv[]){ 
    if(argc==2) {
        // check where the current HEAD is pointing
        //iterate to the root and print commits on the way till root
    }
    else if(argc==3){
        //go to the reflog file of given branch name and wherever you find a commit
        //iterate over it parents till root and print commits
        if(branch_exists(argv[2])==1){

        }
        else{
            cout<<"Error: "<<branch_name<<" branch doesn't exists"<<endl;
        }
    }
   
}

void reflog(int argc, char* argv[]){ 

    if(argc==2) {
        //print git/logs/HEAD
    }
    else if(argc==3){
        //print git/logs/refs/heads file
        char* branch_name=argv[2];
        if(branch_exists(branch_name)==1){
            string file_path="";
            string branch_(branch_name);
            file_path+=LOG_PATH+branch_;
            //read this file and write its contents

        }
        else{
            cout<<"Error: "<<branch_name<<" branch doesn't exists"<<endl;
        }
    }
   
}