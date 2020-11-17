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

time_t time_in_sec(){
    time_t result = time(nullptr);
    return result;
}

auto print_proper_time(time_t result){
    // cout << asctime(localtime(&result));
    return asctime(localtime(&result));
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


vector<string> return_string_vector(char** tokens, int * n){
    vector<string> words;
    for (int i=0; i<*n; i++){
        string tok(tokens[i]);
        words.push_back(tok);
    }
    return words;
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
    // branch_name = (char*)realloc(branch_name, sizeof(char)*MAX_FILE_NAME_LENGTH);
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

void print_hash_map(map<string, vector<string>> mapp, string label){
    cout<<label<<endl;
    for (auto i1: mapp){
        cout<< "-----iterator ------\nkey- " <<i1.first<<" val-";
        for (auto i: i1.second)
            cout<< i <<" ";
        cout<<endl;
    }
}

char* get_cur_head(){
        string head_content;
        ifstream MyFile(HEAD_PATH);
        getline (MyFile, head_content);
        MyFile.close();

        char head_content_[MAX_FILE_NAME_LENGTH];
        strcpy(head_content_, head_content.c_str());
        char** tokens_head_content_= split_index_line(head_content_, " ");
        // string cur_path(tokens_head_content_[1]);
        // return cur_path;
        return tokens_head_content_[1];
}



auto return_split_content_from_sha(string sha){
    // get secret code and size from indexfile (SIZE_STORE)
    // decompress 
    // simply return
    string content;
    string git_dir_(GIT_DIR);
    string path= git_dir_+"/objects/"+sha.substr(0,2)+"/"+sha.substr(2,38);
    // string path= ".git/objects/b5/22cff36efe4c57d1e3b1977531fa0dca7f5842";
    // const char* path= "/home/ac-optimus/implement_git/copy_sha";
    // cout<<"before reading"<<path<<endl;
    ifstream f_reader(path);
    string final_content;
    while(getline (f_reader, content)){
        final_content+=content+"\n";
     } // compressed data in content
    // pair<int, int> compressed_data= get_compressed_store_data(sha); //secret code, size_store
    // cout<<"content of path  "<< compressed_data.first<< " "<< compressed_data.second<<" "<< content<< " " << endl;

    // char* decompress_string= decompress(content, compressed_data.first, compressed_data.second);
    // print_string(decompress_string, compressed_data.second);
    // split based on "\n"
    long long int content_size=final_content.length();
    char content_[content_size];
    strcpy(content_,final_content.c_str());
    // cout<< "blah! "<<content_<<endl;
    int len=0;
    char** lines= split_index_line(content_,"\n",&len);

    vector<string> v;
    for(int i=0;i<len;i++){
        v.push_back(string(lines[i]));
        // cout<<"--------------------------"<<string(lines[i])<<endl;
    }
    return v;
}


auto get_time_from_commit(string cur_commit, int param=2){ //param= 2 for time; 3 for <count>
    // return_split_content_from_sha(string sha);
    vector<string> entries= return_split_content_from_sha(cur_commit);
    char entries_[MAX_FILE_NAME_LENGTH];

    int commit_time_=0;


    for (int i=2; i<entries.size(); i++){
        strcpy(entries_, entries[i].c_str());
        char** splitted_line= split_index_line(entries_," ");
        

        if ((strcmp(splitted_line[0],"author")==0) || (strcmp(splitted_line[0],"committer")==0)){
            char* commit_time=splitted_line[param]; //considering "author drStrange 1653230490 <count>"
            commit_time_ = stoi(commit_time);
            // for (auto i: entries)
            //      cout<<"....................."<<i<<endl;
            break;
        }
    }
    if (commit_time_==0){
        // for (auto i: entries)
        //      cout<<"....................."<<i<<endl;

        cout<<"Debug: no time found in commit_object"<<endl;
    }
    
    return commit_time_;
}

int update_commit_count(){
    // update commit and return the updated count
    string count;
    int count_int;
    fstream f_reader(PATH_COMMIT_COUNT);
    getline(f_reader, count);
    f_reader.close();
    if (count.compare("")==0)
        count_int=1;
    else
        count_int= stoi(count);
    count_int+=1;
    ofstream f_writer(PATH_COMMIT_COUNT);
    f_writer<< to_string(count_int);
    f_writer.close();
    return count_int-1;
}

string get_commit_message(string sha){
    string content;
    string git_dir_(GIT_DIR);
    string path= git_dir_+"/objects/"+sha.substr(0,2)+"/"+sha.substr(2,38);
    ifstream f_reader(path);
    while(getline (f_reader, content)){
        ;
    }
    return content;
}
