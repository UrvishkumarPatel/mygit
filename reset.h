// void run_reset(){

// }

void reset(int argc, char* argv[]){
    if(argc==2) {
        // run_reset();
        char branch_name[MAX_FILE_NAME_LENGTH];
        get_cur_branch_name(branch_name);
        string sha= get_sha_of_branch(branch_name);
        string branch_name_(branch_name);
        if (sha.compare("")==0)
            remove_dir((char*)ROOT_PATH);
        else{
            run_checkout(branch_name,1);
            // cout<<"reset done!"<<endl;
        }
    } 
    else{
        cout<<"Work in progress! our git currently don't take arguments for reset."<<endl;
    }
}