
void stash_pop(){
string stashsha;
stashsha=getanddeletesha();
cout<<stashsha.substr(0,40)<<endl;
    // checkout(getstash[1]) \\manage conflicts also
string curr_sha;
curr_sha=getsha();
string gitdir(GIT_DIR);
string path =gitdir+"/refs/"+"stash";
ofstream fptr;
fptr.open(path ,ios::trunc);
string p=curr_sha+"\n";
fptr<<p;
fptr.close();
if (stashsha.compare("")==0){
    cout<<"No stash available"<<endl;
    return;
}
cout<<"POP:"<<stashsha<<endl;

stash_checkout(stashsha);



}

void run_stash(string message){

        char master_ref_path[MAX_FILE_NAME_LENGTH];
    strcpy(master_ref_path,REF_HEAD_PATH);
    strcat(master_ref_path, "master");       
    if (isDir(master_ref_path)==0){ // git/refs/heads/master
        cout<<"Initial commit not done"<<endl;
        return;
    }

     if (!is_working_dir_updated()){ //not working
         cout<<"no changes to stash"<< endl;
         return;
     }




    char branch_name[MAX_FILE_NAME_LENGTH];
    get_cur_branch_name(branch_name);
    string cur_sha = get_sha_of_branch(branch_name);
    // co=head->next->next
    
    
    

    string bn(branch_name);    
    string msg="Stashing on "+bn+" : "+message;
    cout<<msg<<endl;

    add_dot();
    
    string stash_hash;
    stash_hash=stash_commit(msg);

    int stash_cnt;
    
    stash_cnt=update_stash_count();
    
    


string gitdir(GIT_DIR);
string path =gitdir+"/refs/"+"stash";
ofstream fptr;
fptr.open(path ,ios::trunc);
string p=stash_hash+"\n";
fptr<<p;
fptr.close();

string logpath(LOG_PATH);
string path2 =logpath+"stash";
string savestashcontent=stash_hash+" "+message+" "+"Stash count= "+to_string(stash_cnt)+"\n";

ofstream sth {path2, std::ios_base::app};


sth << savestashcontent;
sth.close();

cout<<"Getting back to"<<cur_sha<<endl;
stash_checkout (cur_sha);
}



void stash(int argc, char* argv[]){ // ./got.out stash pop
    

   if(argc<3){
        cout<<"Usage: stash -m <message> OR stash pop"<<endl;
        exit(1);
    }
 
    if (argc==3){
        string flag(argv[2]);
        if (flag == "pop"){
            cout<< "stash pop"<<endl;
            stash_pop();
        }
        else{
            cout<< "stash" << flag <<"is not supported by out git implementation"<<endl;
            exit(1);
        }
    }
    else{
        string flag(argv[2]);
        if (flag!= "-m"){
            cout<< "not supported!"<<endl;
            exit(1);
        }
        else{
            
            run_stash(argv[3]);
            cout<< "stashing"<<endl;
        }
    }

}