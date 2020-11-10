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