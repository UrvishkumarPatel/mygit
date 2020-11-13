int DEFAULT;

int isDir(char* PATH){
    /* Returns
            0 -- PATH is not present
            1 -- PATH is a directory
            2 -- PATH is a regular file
    */
    struct stat check_file; // some other name please
    if (stat(PATH, &check_file)==-1){ // 0 when file exist
        // printf("cannot stat on %s location!\n", PATH);  //are you planning to print this?
        return 0;
    }
    if (S_ISDIR(check_file.st_mode)) return 1;
    if (S_ISREG(check_file.st_mode)) return 2;
    return -1;

}


char** split_index_line(char * line_, string delimiter_,  int * n=&DEFAULT){
	// https://www.man7.org/linux/man-pages/man3/strsep.3.html
	// char *strsep(char **stringp, const char *delim);
    char delimiter[MAX_FILE_NAME_LENGTH];
    strcpy(delimiter, delimiter_.c_str());
	int tok_nos = TOKEN_NOS;
	char **args = (char**)malloc(tok_nos * sizeof(char*));
	int i = 0;
	while(1){
		if (i>=tok_nos)
		{
			tok_nos+=TOKEN_NOS;
			args = (char**)realloc(args, sizeof(char*)*tok_nos);
		}

		args[i] = strsep(&line_ , delimiter);

		if (args[i]==NULL) break;
		if (strlen(args[i])==0) {
			i--;
		}

		i++;
	}
	// printf("tok_nos : %d\n", tok_nos)

	// printf("no. of args: %d\n", i);
	*n = i;
	return args;
}


// vector<string> return_string_vector(char** tokens, int * n){
//     vector<string> words;
//     for (int i=0; i<n; i++){
//         string tok(tokens[i]);
//         words.push_back(tok);
//     }
//     return words;void threewaymerge(char* current_branch, char* branch_name){

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

// }

int branch_exists(char* branch_name){
	// checks if branch with branch name branch_name exists
    char branch_ref_path[MAX_FILE_NAME_LENGTH];
    strcpy(branch_ref_path,REF_HEAD_PATH);
    strcat(branch_ref_path, branch_name);
        // cout<<branch_ref_path<<endl;
    if(isDir(branch_ref_path)==2) return 1;
    return 0;
}

string get_sha_of_branch(char* branch_name){
    // REF_HEAD_PATH+branch_name

    char branch_ref_path[MAX_FILE_NAME_LENGTH];
    strcpy(branch_ref_path,REF_HEAD_PATH);
    strcat(branch_ref_path, branch_name);

    string sha;
    string branch_ref_path_(branch_ref_path);
    ifstream branch_file(branch_ref_path_);
    getline (branch_file, sha);
    branch_file.close();
    return sha;
}



void get_cur_branch_name(char* branch_name){
    string head_content;
    ifstream MyFile(HEAD_PATH);
    getline (MyFile, head_content);
    MyFile.close();
	// cout<<"header content "<<head_content<<endl;
    char head_content_[MAX_FILE_NAME_LENGTH];
    strcpy(head_content_, head_content.c_str());
    char** tokens_head_content_= split_index_line(head_content_, " ");
    char** paths = split_index_line(tokens_head_content_[1],"/");
	// cout<<"token header content "<<tokens_head_content_[0]<<" address "<<tokens_head_content_[1] <<endl;
    // char branch_name[MAX_FILE_NAME_LENGTH];
	strcpy(branch_name, paths[2]);
	// return branch_name;
}