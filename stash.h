
void stash_pop(){
    // stashlog=file.open(logs/ref/stash)
    // if stashlog==empty{
    //     return 
    // }
    // vector<string> getstash;
    // getstash=stashlog.readlastline;
    // delete lastline;
    // checkout(getstash[1]) \\manage conflicts also
    ;

}

void run_stash(){

    if (!is_working_dir_updated()){
        cout<<"no changes to stash"<< endl;
        return;
    }

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

    // c1=commit(parent=c0,name="index on <current branch> : c0_hash c0_name");

    // add_dot();
    // c2=commit(parent= c0, c1,name=name="WIP on <current branch> : c0_hash c0_name");

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
//   write(hash(c2), ./refs/stash);
//   stashlog=file.open(logs/ref/stash)

//   vector<string> savestash
    
//     if (num_stashes==1){
//         savestash[0]="0"*40

//     }
//     else {
//        savestash[0]=stashlog_lastline[1]
//     }
    
//     savestash[1]=c2_hash;
//     savestash[2]=userID;
//     savestash[3]=c2_name;
  

// checkout (previous commit);
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
            cout<< "stash" << flag <<"is not supported by our git implementation"<<endl;
            exit(1);
        }
    }
}