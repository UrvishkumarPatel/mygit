
// #include "sha1.hpp"
// // #include <string>
// // #include <iostream>
// #include <fstream>
// #include <bits/stdc++.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <stdio.h> // removes
// #include <string.h>
// #include <dirent.h>
// #include <sys/stat.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <unistd.h>
// #include "checkDir.h"
// using namespace std;

vector<string> parent_shas(string cur_commit){
    vector<string> p_shas;
    
    vector<string> entries= return_split_content_from_sha(cur_commit);
    char entries_[MAX_FILE_NAME_LENGTH];
    strcpy(entries_, entries[1].c_str());
    char** splitted_line= split_index_line(entries_," ");
    
    char entries_2[MAX_FILE_NAME_LENGTH];
    strcpy(entries_2, entries[2].c_str());
    char** splitted_line2= split_index_line(entries_2," ");


    if (strcmp(splitted_line[0],"parent")==0){
        char* p_sha=splitted_line[1];
        string p_sha_(p_sha);  
        p_shas.push_back(p_sha_);
    }
    if (strcmp(splitted_line2[0],"parent")==0){
        char* p_sha2=splitted_line2[1];
        string p_sha_2(p_sha2);
        p_shas.push_back(p_sha_2);
    }
    
    return p_shas;
// new3           -
// new2          ---
// master---------------
// new      --

}





int is_parent(string target_sha, string cur_sha){
    if (target_sha.compare(cur_sha)==0)
        return 1;
    // get parent of cur_sha
    vector<string> parent_shas_array= parent_shas(cur_sha);
    // if no parent return 0

    if (parent_shas_array.empty())
        return 0;

    int anyParent= 0;
    for (int indx=0; indx< parent_shas_array.size(); indx++)
        anyParent = anyParent || is_parent(target_sha, parent_shas_array[indx]);
    return anyParent;
}



int is_ancestor(char* current_branch, char* branch_name){
    //checks if the current_branch is the ancenstor of the branch_name
    //returns 1 if yes else 0
    string sha_target= get_sha_of_branch(current_branch);
    string sha_branch= get_sha_of_branch(branch_name);
    int status= is_parent(sha_target, sha_branch);

    return status;
}

void fastforwardmerge(char* current_branch, char* branch_name){
    string copy_sha= get_sha_of_branch(branch_name);
    
    // todo ///////
    // check for staging area
    update_working_dir(copy_sha);
    ofstream index_file(PATH_INDEX, ofstream::trunc);
    index_file<< "";
    index_file.close();
    add_dot();
    // run_checkout(branch_name);
    ///////////////
    
    string ref_head(REF_HEAD_PATH);
    ofstream ref_file(ref_head+current_branch);//# define REF_HEAD_PATH "git/refs/heads/"
    ref_file<< copy_sha;
    ref_file.close();
    
}

// void dummy_checkout(string sha){  //beware while using this function
//     map<string, vector<string>> hashMap;
//     // vector<string> cur_vec;

//     update_working_dir(sha);
//     // ofstream head_file(HEAD_PATH);
//     // string branch_name(name_of_branch);
//     // head_file<< "ref: refs/heads/"+branch_name;
//     // head_file.close();
//     ofstream index_file(PATH_INDEX, ofstream::trunc);
//     index_file<< "";
//     index_file.close();
//     add_dot();
    
// }


// map<string, vector<string>> return_index_dict(string sha){
    
//     dummy_checkout(commit_sha);
//     map<string, vector<string>> hashMap;
//     // vector<string> cur_vec;

//     char** tokens;
//     string line;
//     ifstream index_reader(PATH_INDEX);
//     int n;
//     while(getline(index_reader, line)){
//         tokens= split_index_line(line, " " , &n);
//         vector<string> words= return_string_vector(tokens, &n);
//         hashMap[words[3]].push_back(words[0]);
//         hashMap[words[3]].push_back(words[1]);
//         hashMap[words[3]].push_back(words[2]);
//         // = cur_vec;
//     }
//     return hashMap;
//     // {
//     //     demo/pp/t.txt : mode askjkdjsdljsflasldfaskd 0,
//     // }
// }




// map<string, vector<string>> diff(map<string, vector<string>> master, map<string, vector<string>> branch){
//     /*
//     each line will have suffix 
    
//         - '+' --> not in master but in branch
//         - '-' --> not in branch but in master
//         - '#' --> same but edited. (have different sha or mode)
//     */
//     // todo
//     map<string, vector<string>> diff_map;
//     // entries= master_indx.key() + indx.key()
//     // int n = entries.length();

//     // for pathi in paths_:
//     // for(int i=0; i<n; i++){
//     //     ;
//     // }
//         // if pathi in master_indx and not in indx:
//         //     '-'
//         // elif pathi not in master_indx and in indx:
//         //     '+'
//         // elif pathi in master_indx and in indx:
//         //     if master_indx[pathi][1]!= indx[pathi][1] or master_indx[pathi][0] != indx[pathi][0]:
//         //         '#'

//     return diff_map;
//     // {
//     //     demo/pp/t.txt : [mode, askjkdjsdljsflasldfaskd, 0, +],
//     // }
// }

string LCA(char* bl, char* b2){
    string ancestor_sha;
    // todo
    return ancestor_sha;
}

// void threewaymerge(char* current_branch, char* branch_name){

//     //////////////////////////////////////////////// todo
//     //create a new merge-commit object
//     // iterate in both current_branch and branch_name and create the merged objec
//     //update master to merged object
//     //update the current working directory according to sha of merged commit/master

//     // current_branch ka parent upar he branch_name se
//     //find sha of lcs  and get the index map
//     ////////////////////////////////////////////

//     string ancestor_sha = LCA(branch_name, current_branch);
//     string sha_y= get_sha_of_branch(branch_name);
//     string sha_x= get_sha_of_branch(current_branch);
//     // assume executing "git merge y" being on branch x
//     //     m
//     //    /|
//     //   / |
//     // (y)(x)*
//     //  | /
//     //  |/
//     //  merged

//     map<string, vector<string>> indx_m= return_index_dict(ancestor_sha);
//     map<string, vector<string>> indx_y= return_index_dict(sha_y);
//     map<string, vector<string>> indx_x= return_index_dict(sha_x);

//     map<string, vector<string>> diff_x= diff(indx_m, indx_x);
//     map<string, vector<string>> diff_y= diff(indx_m, indx_y);

//     // paths_= m_index.key()+ d_x.keys() + d_y.keys()

//     // // vector<string> all_paths;
//     // HashSet<ValueType> all_paths;
//     // for (auto i : indx_x)
//     //     all_paths.add(i);

//     // for (auto j : indx_y)
//     //     all_paths.add(j);
        
//     // for (auto k : indx_master)
//     //     all_paths.add(k);
    
//     // for (auto pathi : all_paths){
//     //     if (indx_m.find(pathi) != indx_m.find()){
//     //         if indx_x[pathi]= 
//     //     }
//     // }
    
// //     for pathi in paths_:
// //         if pathi in m_index:
// //             if d_x[0]== '#' or d_y[0]=="#":
// //                 conflict
// //             else if d_x[0]=='-' or d_y[0]=='-':
// //                 pass
// //         else:
// //             if d_x[0]== '+' and d_y[0]== '+':
// //                 conflict
// //             else:
// //                 add to index file

// // m-1	dx	dy	
// // 	-	-	-
// // 	#	#	#
// // 	-	#	#
// // 	#	- 	#
// // 	-		-		
// // m-0	
// //     +'	+'	#
// // 	+'		+'
// // 		+'	+'


//     //

// }


void merge(int argc, char* argv[]){ // merge branch_name into current_branch(master)

    if(argc==2) {
        printf("Give branch name\n");
        return;
    } 
    char* branch_name= argv[2];
    char current_branch[MAX_FILE_NAME_LENGTH];
    // char* current_branch= get_cur_branch_name();
    get_cur_branch_name(current_branch);
    cout<<"the current brach is "<<current_branch<<endl;
    
    if (branch_exists(branch_name)==1){
            //check if current branch is linear with branch_name
            //if at any point both shas are equal of branches 
        if (is_ancestor(current_branch, branch_name)){
            fastforwardmerge(current_branch,branch_name);
        }
        
        else if(is_ancestor(branch_name, current_branch)){
            cout<<"Already up to date"<<endl;
        }
        
        else{
            // threewaymerge(current_branch,branch_name);
        }
    }
    
    else{
        //if branch doesnt exist
        cout<<"Error: "<<branch_name<<" branch doesn't exists"<<endl;
    }
}