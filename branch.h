
// #include <bits/stdc++.h>
// #include<stdio.h>
// #include<cstdlib>
// #include<iostream>
// #include<string.h>
// #include<fstream>
// #include<dirent.h>
// #include <sys/types.h>
// using namespace std;

// # define MAX_FILE_NAME_LENGTH 1024
//     //    #include <dirent.h>
// // #define PATH_INDEX "git/index"
// // #define ROOT_PATH "."
// // #define MAX_FILE_NAME_LENGTH 1024
// // #define PATH "git/refs/heads/master"
// # define REF_HEAD_PATH "git/refs/heads/"
// # define GIT_PATH "git/"
// # define HEAD_PATH "git/HEAD"

void update_refs(char* branchname){
    string head_content;
    ifstream MyFile(HEAD_PATH);
    getline (MyFile, head_content);
    MyFile.close();

    char head_content_[MAX_FILE_NAME_LENGTH];
    strcpy(head_content_, head_content.c_str());
    char** tokens_head_content_= split_index_line(head_content_, " ");
    
    // cout<< tokens_head_content_[1] << endl;

    string ref_path(tokens_head_content_[1]);
    string commit_sha;
    ifstream ref_file(GIT_PATH+ref_path);
    getline (ref_file, commit_sha);
    ref_file.close();

    string branchname_(branchname);

    // cout << REF_HEAD_PATH+branchname_<< endl;

    ofstream new_file(REF_HEAD_PATH+branchname_);
    new_file<<commit_sha;
    new_file.close();

    // cat .git/HEAD

    // //  ref: refs/heads/master
    // // 4e65764bd8221e0ef0974c9797767289aba6b505   detached head
    // symbolic pointer

    // cat .git/refs/heads/branchname
}




void branch(int argc, char* argv[]){
   if(argc==2){
        // print all branches and highlight the name of checked out branch(pointed by heads)
        char* cur_branch= get_cur_branch_name();

        DIR *pDIR;
        struct dirent *entry;
        if( pDIR=opendir(REF_HEAD_PATH) ){
                while(entry = readdir(pDIR)){
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
        update_refs(argv[2]);
        // cout<< "some print"<<endl;
    }
}
