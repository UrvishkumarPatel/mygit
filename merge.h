
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

void threewaymerge(char* current_branch, char* branch_name){
    //create a new merge-commit object
    // iterate in both current_branch and branch_name and create the merged objec
    //update master to merged object
    //update the current working directory according to sha of merged commit/master

    // current_branch ka parent upar he branch_name se
    int a=0;

    // git merge new2

    // index_file= new2

    // for line in new
    //     if  line in index_file:
    //         check for conflict
    //     if not present:
    //         if not present in master:
    //             add to the index file
    //         else:
    //             pass

    // check for conflict:{
    //     ofstream characters:f1 and f2
    //     while (f1!=NULL & f1!=NULL){
    //         if cmp(f1,f2)!=0{
    //             return 1
    //         }
    //     }
    //     return 0;
    // }

// {
//     demo/pp/t.txt : mode askjkdjsdljsflasldfaskd 0,

    
// }
// def diff(master_indx, indx):
//     """
//     each line will have prefix 
    
//         - '+' --> not in master but in branch
//         - '-' --> not in branch but in master
//           '#' --> same but edited. (have different sha)
//     """
//     paths_= master_indx.key() + indx.key()
//     for pathi in paths_:
//         if pathi in master_indx and not in indx:
//             '-'
//         elif pathi not in master_indx and in indx:
//             '+'
//         elif pathi in master_indx and in indx:
//             if master_indx[pathi][1]!= indx[pathi][1] or master_indx[pathi][0] != indx[pathi][0]:
//                 '#'
        



// {
//     demo/pp/t.txt : [+, mode, askjkdjsdljsflasldfaskd, 0],


// }
//     return diff

//     m_index
//     x_index = 
//     y_index
//     d_x= diff(m_index, x_index)
//     d_y= diff(m_index, y_index)


//     paths_= m_index.key()+ d_x.keys() + d_y.keys()


//     for pathi in paths_:
//         if pathi in m_index:
//             if d_x[0]== '#' or d_y[0]=="#":
//                 conflict
//             else if d_x[0]=='-' or d_y[0]=='-':
//                 pass
//         else:
//             if d_x[0]== '+' and d_y[0]== '+':
//                 conflict
//             else:
//                 add to index file

// m-1	dx	dy	
// 	-	-	-
// 	#	#	#
// 	-	#	#
// 	#	- 	#
// 	-		-		
// m-0	
//     +'	+'	#
// 	+'		+'
// 		+'	+'


}


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
            threewaymerge(current_branch,branch_name);
        }
    }
    
    else{
        //if branch doesnt exist
        cout<<"Error: "<<branch_name<<" branch doesn't exists"<<endl;
    }
}