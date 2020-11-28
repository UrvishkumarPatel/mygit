/* checkout implementation*/
void build_dfs(string tree_sha, string curPath_){
    // // args= ["tree", "blobs"]
    // void build_dfs(string tree_sha, string curPath_):
    // for line in tree_object:
    //     if "tree":
    //         mkdir(curPath_)
    //         build_dfs(subtree_sha, new_curPath)
    //     if "blob":
    //         write file

    vector<string> entries= return_split_content_from_sha(tree_sha);
    // cout<< " print "<< entries[0]<<endl;
    // cout<<"entries below:"<<endl;
    // for (int idx=0; idx<entries.size(); idx++)
    //     cout<<entries[idx]<<endl;

    // char* entries[]= {"100644 tree e69de29bb2d1d6434b8b29ae775ad8c2e48c5391 demo",
    //                 "100644 blob e69de29bb2d1d6434b8b29ae775ad8c2e48c5391 b.txt"};
    char curPath[MAX_FILE_NAME_LENGTH];
    strcpy(curPath, curPath_.c_str());
    // mkdir(curPath, 0777);
    // char curPath[MAX_FILE_NAME_LENGTH];
    for (int i=0; i< entries.size(); i++){
        char entries_[MAX_FILE_NAME_LENGTH];
        strcpy(entries_, entries[i].c_str());
        char** entry = split_index_line(entries_, " ");

        if (strcmp(entry[1],"blob") == 0){
            // cout<< "inside if"<<endl;
        // if (entry[1].compare("blob") == 0){
            string file_name(entry[3]);
            string path = curPath_+"/"+file_name;
            ofstream blob_file(path);
            // blob_file << commit_sha;
            // add the content -- add mode
            blob_file<<return_content(entry[2]);
            // blob_file<< content;
            blob_file.close();
        }
        else{
            // cout<< "inside else"<<endl;
            string dir_name= entry[3];
            // string dir_name(entry[3]);
            string path = curPath_+"/"+dir_name;
            strcpy(curPath, path.c_str());
            mkdir(curPath, 0777);
            build_dfs(entry[2], path);
        }
    }
}


void write_dir(string commit_sha){ 
    // runs build_dfs
    // extract content of commit object
    vector<string> entries= return_split_content_from_sha(commit_sha);
    // split entries[0] and get sha
    // char** split_index_line(char * line_, string delimiter_,  int * n=&DEFAULT){
    char entries_[MAX_FILE_NAME_LENGTH];
    strcpy(entries_, entries[0].c_str());


    
    char first_line[MAX_FILE_NAME_LENGTH];
    strcpy(first_line, entries_);
    char** splitted_line= split_index_line(first_line," ");
    char* tree_sha=splitted_line[1];
    // get sha of tree node
    // pass it to dfs:
    build_dfs(tree_sha, ROOT_PATH);
}

void update_working_dir(string commit_sha){
    /////// check this first////
    // string pathname(ROOT_PATH);
    remove_dir((char*)ROOT_PATH);
    ///////
    write_dir(commit_sha);
}


void stash_checkout(string commit_sha){ 
    // runs update_working_dir
    update_working_dir(commit_sha);
    
    // update head path
    
    // del indexfile, and create new
    // char path_indx[MAX_FILE_NAME_LENGTH];
    // strcpy(path_indx, PATH_INDEX);
    ofstream index_file(PATH_INDEX, ofstream::trunc);
    // string branch_name(argv[2]);
    index_file<< "";
    index_file.close();
    // remove_file(path_indx);
    // iterate over ROOT_PATH and ignore .git
    add_dot();
}


void run_checkout(char* name_of_branch, int dummy_flag=0){ 
    // runs update_working_dir
    char branch_ref_path[MAX_FILE_NAME_LENGTH];
    strcpy(branch_ref_path,REF_HEAD_PATH);
    strcat(branch_ref_path, name_of_branch);
    // cout<<branch_ref_path<<endl;
    
    // if(isDir(branch_ref_path)==2){
    if (branch_exists(name_of_branch)==1){
        char previous_branch[MAX_FILE_NAME_LENGTH];
        get_cur_branch_name(previous_branch);

        string sha;
        string branch_ref_path_(branch_ref_path);
        ifstream branch_file(branch_ref_path_);
        getline (branch_file, sha);
        branch_file.close();

        update_working_dir(sha);
        // update head path
        ofstream head_file(HEAD_PATH);
        string branch_name(name_of_branch);
        head_file<< "ref: refs/heads/"+branch_name;
        head_file.close();
        // del indexfile, and create new
        // char path_indx[MAX_FILE_NAME_LENGTH];
        // strcpy(path_indx, PATH_INDEX);
        ofstream index_file(PATH_INDEX, ofstream::trunc);
        // string branch_name(argv[2]);
        index_file<< "";
        index_file.close();
        // remove_file(path_indx);
        // iterate over ROOT_PATH and ignore .git
        add_dot();
        if (dummy_flag==0){
            string prev_sha = get_sha_of_branch(previous_branch);
            string commit_message = get_commit_message(prev_sha);
            cout<<"Previous HEAD position was "+prev_sha+" "+commit_message<<endl;
            cout<<"Switched to branch \'"<<name_of_branch<<"\'"<<endl;
        }
        else{
            ;  //reset
        }
    }
    else{
        cout<<"Error: branch doesn't exist"<<endl;
        exit(0);
    }
}

int is_working_dir_updated(){
    // check if current working directory is updated
    write_object_flag=0;
    // read index file
    string index_data = "";
    string line;
    ifstream myfile(PATH_INDEX);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            index_data+=line+"\n";
        }
        myfile.close();
    }
    /////////////////

    add_dot();

    char current_branch[MAX_FILE_NAME_LENGTH];
    get_cur_branch_name(current_branch);
    string commit_sha = get_sha_of_branch(current_branch);

    vector<string> entries= return_split_content_from_sha(commit_sha);
    char entries_[MAX_FILE_NAME_LENGTH];
    strcpy(entries_, entries[0].c_str());
    char** splitted_line= split_index_line(entries_," ");
    char* tree_sha=splitted_line[1];
    string old_root(tree_sha);

    string new_root = return_root_sha_from_index();

    // write index file
    ofstream fptr;
    fptr.open(PATH_INDEX, ofstream::trunc);
    fptr<< index_data;
    fptr.close();
    ///////////////

    write_object_flag=1;
    
    if (new_root.compare(old_root)==0){
        // cout<<"Nothing to commit."<<endl;
        return 0;
    }
    else{
        return 1;
    }
}

void checkout(int argc, char* argv[]){ 
    // checkout to passed branch name
    // argv[2] --  branch name
    if(argc==2) {
        printf("Give branch name\n");
        return;
    } 
    else if(argc==3){

        ///////////////////////// WORK UNDER PROGRESS!
        // update reset after this
        // making checkout more robust // incomplete testing
        // if (is_working_dir_updated()){
        //     cout<< "error: Your changes to the files would be overwritten by checkout:" << endl;
        //     cout<< "Please commit your changes or stash them before you switch branches.\nAborting"<< endl;
        //     return;
        // }
        ///////////////////////

        char current_branch[MAX_FILE_NAME_LENGTH];
        get_cur_branch_name(current_branch);
        string curr_(current_branch);
        
        run_checkout(argv[2]);

        //get sha of current branch
        string branch_(argv[2]);
        string sha_curr = get_sha_of_branch(argv[2]);

        //defining checkout log content
        string checkout_log_content;
        checkout_log_content=sha_curr+" imp_git imp_git checkout: moving from "+curr_+" to "+branch_;

        //writing in git/logs/HEAD
        ofstream log_head;
        log_head.open(LOG_HEAD_PATH,ofstream::app);
        log_head<<checkout_log_content<<'\n';
        log_head.close();
        return;
    }
    else{
        cout<<"Error"<<endl;
        exit(1);
    }
}
