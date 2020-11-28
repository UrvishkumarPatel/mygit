void iter_ancestor(string cur_sha){
    //iterate in parents and print all the previous commit
    string log_content=return_commitlog_content(cur_sha);
    cout<<"commit : "+cur_sha<<endl;
    cout<<log_content<<endl;

    // get parent of cur_sha
    vector<string> parent_shas_array= parent_shas(cur_sha);
    
    // if no parent return 0
    if (parent_shas_array.empty())
        return;

    for (int i=0; i< parent_shas_array.size(); i++){
        iter_ancestor(parent_shas_array[i]);
    }
}


void log(int argc, char* argv[]){ 
    //log without any arguement iterates in the current checkedout branch
    if(argc==2) {
        // check where the current HEAD is pointing
        char master_ref_path[MAX_FILE_NAME_LENGTH];
        strcpy(master_ref_path,REF_HEAD_PATH);
        strcat(master_ref_path, "master");       
        if (isDir(master_ref_path)==0){ // git/refs/heads/master
            cout<<"Initial commit not done"<<endl;
            return;
        }
        char current_branch[MAX_FILE_NAME_LENGTH];
        get_cur_branch_name(current_branch);
        string curr_(current_branch);
        string sha_curr = get_sha_of_branch(current_branch);

        //iterate to the root and print commits on the way till root
        iter_ancestor(sha_curr);
    }
    //log with branch as arguement iterates in that branch
    else if(argc==3){
        char* branch_name=argv[2];
        //go to the reflog file of given branch name and wherever you find a commit
        //iterate over it parents till root and print commits
        if(branch_exists(branch_name)==1){
            string sha_curr = get_sha_of_branch(branch_name);
            //iterate to the root and print commits on the way till root
            iter_ancestor(sha_curr);
        }
        else{
            cout<<"Error: "<<branch_name<<" branch doesn't exists"<<endl;
        }
    }
   
}

void reflog(int argc, char* argv[]){ 
    //reflog prints previous commits, checkouts and merges
    //without any arguement it prints contents of the git/logs/HEAD file
    if(argc==2) {
        //print git/logs/HEAD
        string line;
        ifstream log_head(LOG_HEAD_PATH);
        if(log_head.is_open()){
            while(getline(log_head, line)){
                cout<<line<<endl;
            }
        }
        else{
            cout<<"Error"<<endl;
            exit(1);
        }

    }
    //with branch as arguement it prints data stored in git/logs/refs/branch_name
    else if(argc==3){
        //print git/logs/refs/branch_name file
        char* branch_name=argv[2];
        if(branch_exists(branch_name)==1){
            string file_path="";
            string branch_(branch_name);
            file_path+=LOG_PATH+branch_;
            //read this file and write its contents
            string line;
            ifstream log_branch(file_path);
            if(log_branch.is_open()){
                while(getline(log_branch, line)){
                    cout<<line<<endl;
                }
            }
            else{
                cout<<"Error"<<endl;
                exit(1);
            }
        }
        else{
            cout<<"Error: "<<branch_name<<" branch doesn't exist"<<endl;
        }
    }
   
}
