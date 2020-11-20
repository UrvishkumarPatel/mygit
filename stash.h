
void stash_pop(){
    ;

}

void run_stash(){

    char master_ref_path[MAX_FILE_NAME_LENGTH];
    strcpy(master_ref_path,REF_HEAD_PATH);
    strcat(master_ref_path, "master");       
    if (isDir(master_ref_path)==0){ // git/refs/heads/master
        cout<<"Initial commit not done"<<endl;
        return;
    }

    char branch_name[MAX_FILE_NAME_LENGTH];
    get_cur_branch_name(branch_name);
    string cur_sha = get_sha_of_branch(branch_name);
    // co=head->next->next

// //////////////////////////
//     add_dot(); // not sure

//     c1=commit(parent=c0);

//     // c1: "index on <branch> : co_hash co_name
//     // Saved working directory and index state 
//     // WIP on newb: 5d2a6fa dff 
//     c2=commit(parent= c0, c1);
//         // string get_content_merge_commit(string root_sha, string commit_msg, string parent_1, string parent_2, time_t cur_time, string count){
//         //     string author= "imp_git";
//         //     string commiter= "imp_git";
//         //     string parent_content= "parent "+parent_1+"\nparent "+parent_2+"\n";
//         //     string t = to_string(cur_time);

//         //     string content= "tree "+root_sha + "\n"+ parent_content+"author "+ author + " " + t + " " + count + "\n" + "committer "+commiter+ " " + t + " " + count +"\n\n"+ commit_msg;
//         //     return content;
//         // }
//     // write(hash(c2), ./refs/stash);
//     // checkout (previous commit);
//     // f  

// ////////////////////////////  

}



void stash(int argc, char* argv[]){ // ./got.out stash pop
   if(argc==2){
        run_stash();
    }
 
    if (argc==3){
        string flag(argv[2]);
        if (flag == "pop"){
            cout<< "stash pop"<<endl;
        }
        else{
            cout<< "stash" << flag <<"is not supported by out git implementation"<<endl;
            exit(1);
        }
    }
}