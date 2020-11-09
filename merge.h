

#include "zlib.h"

#include "sha1.hpp"
// #include <string>
// #include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h> // removes
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "checkDir.h"
using namespace std;


int LCA(current_branch,branch_name){
    //checks if the current_branch is the ancenstor of the branch_name
    //returns 1 if yes else 0
}

void fastforwardmerge(current_branch,branch_name){
    //copy sha of branch_name into current_branch
    //update the current working directory according to sha of branch_name
}

void threewaymerge(current_branch,branch_name){
    //create a new merge-commit object
    // iterate in both current_branch and branch_name and create the merged objec
    //update master to merged object
    //update the current working directory according to sha of merged commit/master
}
void merge(current_branch,branch_name){
    //check if branch_name exits
        //check if current branch is linear with branch_name

        //if at any point both shas are equal of branches 
        cout<<"Already up to date"<<endl;

            //else
            LCA(current_branch,branch_name)
            //if LCA is 1, then do fastforward merge 
            fastforwardmerge(current_branch,branch_name)
            //if LCA is 0, 3-way merge
            threewaymerge(current_branch,branch_name)

    //if branch doesnt exist
    cout<<"Cannot merge "<<branch_name<<endl;
}