/* branch implementation*/

void update_refs(char* branchname){
    //getting name of the curent branch which is stored at git/HEAD
    string head_content;
    ifstream MyFile(HEAD_PATH);
    getline (MyFile, head_content);
    MyFile.close();
    char head_content_[MAX_FILE_NAME_LENGTH];
    strcpy(head_content_, head_content.c_str());
    char** tokens_head_content_= split_index_line(head_content_, " ");
    
    //getting sha of cuurent branch    
    string ref_path(tokens_head_content_[1]);
    string commit_sha;
    ifstream ref_file(GIT_PATH+ref_path);
    getline (ref_file, commit_sha);
    ref_file.close();

    //Creating a file at git/refs/heads/ with filename git/refs/heads/branchname
    string branchname_(branchname);
    ofstream new_file(REF_HEAD_PATH+branchname_);
    //sha of current branch gets stored in that filename
    new_file<<commit_sha;
    new_file.close();

}




void branch(int argc, char* argv[]){
   if(argc==2){
        // print all branches and highlight the name of checked out branch(pointed by heads)
        char cur_branch[MAX_FILE_NAME_LENGTH];
        get_cur_branch_name(cur_branch);
        DIR *pDIR;
        struct dirent *entry;
        if( pDIR=opendir(REF_HEAD_PATH) ){
                while(entry = readdir(pDIR)){
                        //ignore the current and parent directory
                        if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
                            if (strcmp(entry->d_name, cur_branch) == 0) {cout<<"*";}
                            else {cout<<" ";}
                            
                            cout << " " << entry->d_name << "\n";
                        }
                        
                }
                closedir(pDIR);
        }
        return;
    }
    else{
        //get te sha of the current branch
        update_refs(argv[2]);
        //Branch completed


        //Store information for log and reflog

        //Get the current branch name
        char current_branch[MAX_FILE_NAME_LENGTH];
        get_cur_branch_name(current_branch);
        string branch_(current_branch);
        //sha for current branch
        string sha_curr = get_sha_of_branch(current_branch);
            
        //Creating content for log files
        string log_branch_content;
        log_branch_content=sha_curr+" imp_git imp_git branch: Created from "+branch_;

        //writing in git/logs/refs/current_branch
        string new_branch(argv[2]);
        string branch_log_path;
        branch_log_path=LOG_PATH+new_branch;
        ofstream log_file;
        // cout<<"Making new file "<<branch_log_path<<endl;
        log_file.open(branch_log_path,ofstream::app);
        log_file<<log_branch_content<<'\n';
        log_file.close();
    }
}
