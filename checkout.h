// #include <bits/stdc++.h>
// #include<stdio.h>
// #include<cstdlib>
// #include<iostream>
// #include<string.h>
// #include<fstream>
// #include<dirent.h>
// #include <sys/types.h>

// # include "rm.h"
// using namespace std;

// # define MAX_FILE_NAME_LENGTH 1024
// # define REF_HEAD_PATH "git/refs/heads/"
// # define GIT_PATH "git/"
// # define HEAD_PATH "git/HEAD"
// # define ROOT_PATH "."

void build_dfs(string tree_sha, string curPath_){
    // // args= ["tree", "blobs"]
    // // mkdir
    // for subtree_sha in args:
    //     if "tree":
    //         dfs(subtree_sha, new_curPath)
    //         // recurese

    //     if blob:
    //         //  wrwite file

    //     else:
    //         // terminate

    vector<string> entries= return_split_content_from_sha(tree_sha);
    // cout<< " print "<< entries[0]<<endl;
    // cout<<"entries below:"<<endl;
    // for (int idx=0; idx<entries.size(); idx++)
    //     cout<<entries[idx]<<endl;

    // char* entries[]= {"100644 blob e69de29bb2d1d6434b8b29ae775ad8c2e48c5391 a.txt",
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
            cout<< "inside if"<<endl;
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
            cout<< "inside else"<<endl;
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


// int branch_exists(char* branch_name){
//     char branch_ref_path[MAX_FILE_NAME_LENGTH];
//     strcpy(branch_ref_path,REF_HEAD_PATH);
//     strcat(branch_ref_path, branch_name);
//         // cout<<branch_ref_path<<endl;
//     if(isDir(branch_ref_path)==2) return 1;
//     return 0;
// }



// string get_sha_of_branch(string branch_name){
//     // REF_HEAD_PATH+branch_name

//     char branch_ref_path[MAX_FILE_NAME_LENGTH];
//     strcpy(branch_ref_path,REF_HEAD_PATH);
//     strcat(branch_ref_path, branch_name);

//     string sha;
//     string branch_ref_path_(branch_ref_path);
//     ifstream branch_file(branch_ref_path_);
//     getline (branch_file, sha);
//     branch_file.close();
//     return sha;

// }




void run_checkout(char* name_of_branch){
    char branch_ref_path[MAX_FILE_NAME_LENGTH];
    strcpy(branch_ref_path,REF_HEAD_PATH);
    strcat(branch_ref_path, name_of_branch);
    // cout<<branch_ref_path<<endl;
    
    // if(isDir(branch_ref_path)==2){
    if (branch_exists(name_of_branch)==1){
    
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
    }
    else{
        cout<<"Error: branch doesn't exist"<<endl;
        exit(0);
    }
}


void checkout(int argc, char* argv[]){ // argv[2] --  branch name
    if(argc==2) {
        printf("Give branch name\n");
        return;
    } 
    else if(argc==3){
        // string branch_name(argv[2]);
        char current_branch[MAX_FILE_NAME_LENGTH];
        get_cur_branch_name(current_branch);
        string curr_(current_branch);
        
        run_checkout(argv[2]);

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
