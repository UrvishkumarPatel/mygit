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
    //checks if the current_branch is the ancestor of the branch_name
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

void dummy_checkout(string sha){  //beware while using this function
    map<string, vector<string>> hashMap;
    // vector<string> cur_vec;

    update_working_dir(sha);
    // ofstream head_file(HEAD_PATH);
    // string branch_name(name_of_branch);
    // head_file<< "ref: refs/heads/"+branch_name;
    // head_file.close();
    ofstream index_file(PATH_INDEX, ofstream::trunc);
    index_file<< "";
    index_file.close();
    add_dot();
    
}


map<string, vector<string>> return_index_dict(string sha){
    
    dummy_checkout(sha);
    map<string, vector<string>> hashMap;
    // vector<string> cur_vec;

    char** tokens;
    char line_[MAX_FILE_NAME_LENGTH];
    string line;
    ifstream index_reader(PATH_INDEX);
    int n;
    while(getline(index_reader, line)){
        // char line_[line.size()+1];
        strcpy(line_, line.c_str());
        tokens= split_index_line(line_, " " , &n);
        vector<string> words= return_string_vector(tokens, &n);
        hashMap[words[3]].push_back(words[0]);
        hashMap[words[3]].push_back(words[1]);
        hashMap[words[3]].push_back(words[2]);
        // = cur_vec;
    }
    return hashMap;
    // {
    //     demo/pp/t.txt : mode askjkdjsdljsflasldfaskd 0,
    // }
}




map<string, vector<string>> diff(map<string, vector<string>> lca, map<string, vector<string>> branch){
    /*
    each line will have suffix 
    
        - '+' --> not in master but in branch
        - '-' --> not in branch but in master
        - '#' --> same but edited. (have different sha or mode)
    */
    // todo

    map<string, vector<string>> diff_map;
    // HashSet<string> entries;
    unordered_set <string> entries;
    // for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) { 
    //     cout << '\t' << itr->first 
    //          << '\t' << itr->second << '\n'; 
    // } 
    for (auto i : branch)
        entries.insert(i.first);
    for (auto k : lca)
        entries.insert(k.first);

    for (auto pathi: entries){
        if ((lca.find(pathi)!= lca.end()) && (branch.find(pathi)== branch.end())){
            diff_map[pathi]= lca[pathi];
            diff_map[pathi].push_back("-"); // by ref? 
        }
        else if((lca.find(pathi)==lca.end()) && (branch.find(pathi)!= branch.end())){
            diff_map[pathi]= branch[pathi];
            diff_map[pathi].push_back("+"); 
        }
        else if((lca.find(pathi)!=lca.end()) && (branch.find(pathi)!= branch.end())){
            if ((lca[pathi][0]!= branch[pathi][0]) || (lca[pathi][1]!= branch[pathi][1])){
                diff_map[pathi]= branch[pathi];
                diff_map[pathi].push_back("#"); 
            }
        }
    }
    // entries= master_indx.key() + indx.key()
    // int n = entries.length();

    // for pathi in paths_:
    //     if pathi in master_indx and not in indx:
    //         '-'
    //     elif pathi not in master_indx and in indx:
    //         '+'
    //     elif pathi in master_indx and in indx:
    //         if master_indx[pathi][1]!= indx[pathi][1] or master_indx[pathi][0] != indx[pathi][0]:
    //             '#'

    return diff_map;
    // {
    //     demo/pp/t.txt : [mode, askjkdjsdljsflasldfaskd, 0, +],
    // }
}

void get_ancestors(unordered_set<string>* ancestor_set, string cur_commit){
    // read the parent sha
    vector<string> cur_parents= parent_shas(cur_commit);
    if (cur_parents.size()==0)
        return; // recurssion termination
    else{
        for (auto parent_i: cur_parents)
            ancestor_set->insert(parent_i);// parent sha appended
        for (auto parent_i: cur_parents)
            get_ancestors(ancestor_set, parent_i);
    }
}

string LCA(char* b1, char* b2){
    // unordered_set<string> ancestor_sha;
    // todo
    ////////////
    string sha_b1 = get_sha_of_branch(b1);
    string sha_b2 = get_sha_of_branch(b2);

    unordered_set<string> ancestor_b1;
    get_ancestors(&ancestor_b1, sha_b1);

    unordered_set<string> ancestor_b2;
    get_ancestors(&ancestor_b2, sha_b2);
    // parent sets ready

    unordered_set<string> common_ancestor;
    for (auto parent_i : ancestor_b1){
        if (ancestor_b2.find(parent_i)!=ancestor_b2.end())
            common_ancestor.insert(parent_i);
    }
    for (auto parent_j : ancestor_b2){
        if (ancestor_b1.find(parent_j)!=ancestor_b1.end())
            common_ancestor.insert(parent_j);
    }
    // lca set ready till here
    for (auto i: common_ancestor)
        cout<< "------------ "<<i<<endl;

    string lca;
    int max= 0;
    int cur;
    for (auto ancestor_i : common_ancestor){
        cur= get_time_from_commit(ancestor_i, 3);
        if (cur> max){
            max= cur;
            lca= ancestor_i;
        }
    }
    cout<<"least common ancestor"<<lca<<endl;
    // ---------------todo--------------get lca from sets

    // string cur_commit = get_sha_of_branch(b1);
    // vector<string> p = parent_shas(cur_commit);
    // ancestor_sha = p[0];
    ////////////
    return lca;
}

vector<string> conflict(string pathname, vector<string> diff_x_indx, vector<string> diff_y_indx, char* current_branch, char* branch_name){
    cout<<"There is a conflict in "<<pathname<<endl;
    cout<<"Which branch do you want to consider for this file?"<<endl;
    cout<<"Enter 1 for "<<current_branch<<" (default)"<<endl;
    cout<<"Enter 2 for "<<branch_name<<endl;
    
    int encoding;
    cin>> encoding;
    if (encoding==1)
        return diff_x_indx;
    else if (encoding==2) 
        return diff_y_indx;
    else{
        cout << "You entered something else; By default branch "<< current_branch << "selected."<<endl;
        return diff_x_indx;
    }
}

void make_index(map<string, vector<string>> index_hash_map){
    string line;
    ofstream f_create;
    f_create.open(PATH_INDEX, ofstream::trunc);
    for (auto entry: index_hash_map){
        for(int i=0; i<3; i++)
            line+=entry.second[i]+" ";
        f_create << line+entry.first << endl;
        line="";
    }
    f_create.close();
}

void threewaymerge(char* current_branch, char* branch_name){

    //////////////////////////////////////////////// todo
    //create a new merge-commit object
    // iterate in both current_branch and branch_name and create the merged objec
    //update master to merged object
    //update the current working directory according to sha of merged commit/master

    // current_branch ka parent upar he branch_name se
    //find sha of lcs  and get the index map
    ////////////////////////////////////////////

    string ancestor_sha = LCA(branch_name, current_branch);
    cout<<"here"<<"lca--"<<ancestor_sha<< endl;
    string sha_y= get_sha_of_branch(branch_name);
    cout<<"here2"<<endl;
    
    string sha_x= get_sha_of_branch(current_branch);
    // assume executing "git merge y" being on branch x
    //     m
    //    /|
    //   / |
    // (y)(x)*
    //  | /
    //  |/
    //  merged

    map<string, vector<string>> indx_m= return_index_dict(ancestor_sha);
    map<string, vector<string>> indx_y= return_index_dict(sha_y);
    map<string, vector<string>> indx_x= return_index_dict(sha_x);

    map<string, vector<string>> diff_x= diff(indx_m, indx_x);
    map<string, vector<string>> diff_y= diff(indx_m, indx_y);

    // paths_= m_index.key()+ d_x.keys() + d_y.keys()
    // HashSet<string> all_paths;
    unordered_set<string> all_paths;
    for (auto i : indx_x)
        all_paths.insert(i.first);
    for (auto j : indx_y)
        all_paths.insert(j.first);
    for (auto k : indx_m)
        all_paths.insert(k.first);
        
    map<string, vector<string>> index_hash_map;
    
    for (auto pathi : all_paths){
        cout<<"pathi: "<<pathi<<endl;
        if (indx_m.find(pathi)!= indx_m.end()){ // present in the lca
            if (diff_x.find(pathi)!= diff_x.end()){// present in x
                if (diff_y.find(pathi)!= diff_y.end()){// present in y 11
                    if ((diff_x[pathi][3].compare("#")==0) || (diff_y[pathi][3].compare("#")==0)){
                        index_hash_map[pathi] = conflict(pathi, diff_x[pathi], diff_y[pathi], current_branch, branch_name); // conflict
                    }
                    else if ((diff_x[pathi][3].compare("-")==0) || (diff_y[pathi][3].compare("-")==0)){
                        ;// pass
                    }
                }
                else{ // not present in y 10
                    if (diff_x[pathi][3].compare("-")==0){
                        ; // -    
                    }
                    if (diff_x[pathi][3].compare("#")==0){
                        cout<<"yaha pe 10"<<endl;
                        index_hash_map[pathi]= diff_x[pathi]; // +
                    }
                }
            }
            else{ // not present in x 
                if (diff_y.find(pathi)!= diff_y.end()){// present in y 01
                    if (diff_y[pathi][3].compare("-")==0){
                        ; // -    
                    }
                    if (diff_y[pathi][3].compare("#")==0){
                        cout<<"yaha pe 01"<<endl;
                        index_hash_map[pathi]= diff_y[pathi]; // +
                    }
                }
                else{ // not present in y 00
                    // add from master
                    index_hash_map[pathi]= indx_m[pathi];
                }
            }
        }
        else{// not present in the lca
            if (diff_x.find(pathi)!= diff_x.end()){// present in x
                if (diff_y.find(pathi)!= diff_y.end()){// present in y
                    //conflict
                    index_hash_map[pathi] = conflict(pathi, diff_x[pathi], diff_y[pathi], current_branch, branch_name);
                }
                else{ // not present in y
                    index_hash_map[pathi]= diff_x[pathi];
                }
            }
            else{ // not present in x
                if (diff_y.find(pathi)!= diff_y.end()){// present in y
                    index_hash_map[pathi]= diff_y[pathi];
                }
            }
        }
    }
    print_hash_map(diff_x, "x");
    print_hash_map(diff_y, "y");
    print_hash_map(index_hash_map, "final");


    string x_name(current_branch);
    string y_name(branch_name);
    string message= "Merge branch "+ x_name+ " into "+y_name;


    make_index(index_hash_map);
    run_commit(message, 1, sha_x, sha_y);

    string commit_sha;
    char* path_= get_cur_head();
    string PATH(path_);
    ifstream f;
    f.open("git/"+PATH);
    getline (f, commit_sha);
    f.close();
    
    update_working_dir(commit_sha);



    // m-1	dx	dy	
    //     -    -	-   11
    //     #    #	#   11
    //     -    #	#   11  
    //     #    - 	#   11
    //     #        +   10 add dy
    //     -        -   10
    //              m   00 add m
    //          #   +   10
    //          -   -   10

    // m-0	
    //     +   +   #
    //     +       +
    //         +   +

    // for pathi in paths_:
    //     if pathi in m_index:
    //         if d_x[0]== '#' or d_y[0]=="#":
    //             conflict
    //         else if d_x[0]=='-' or d_y[0]=='-':
    //             pass
    //         else if pathi not in both d_x and d_y:
    //             add m_index to index
    //     else:
    //         if d_x[0]== '+' and d_y[0]== '+':
    //             conflict
    //         else:
    //             add to index file

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
        int merge=-1;
        if (is_ancestor(current_branch, branch_name)){
            fastforwardmerge(current_branch,branch_name);
            merge=1;
        }
        
        else if(is_ancestor(branch_name, current_branch)){
            cout<<"Already up to date"<<endl;
        }
        
        else{
            threewaymerge(current_branch,branch_name);
            merge=2;
        }
        if(merge!=-1){
            // string branch_(argv[2]);

            string sha_curr = get_sha_of_branch(current_branch);

            //defining merge log content
            string merge_log_content;
            if(merge==1){
                string new_branch(argv[2]);
                merge_log_content=sha_curr+" Merge :"+new_branch+" Fast Forward Merge";
            }
            if(merge==2){
                string new_branch(argv[2]);
                merge_log_content=sha_curr+" Merge :"+new_branch+" Three Way Merge";
            }
            //writing in git/logs/HEAD
            ofstream log_head;
            log_head.open(LOG_HEAD_PATH,ofstream::app);
            log_head<<merge_log_content<<'\n';
            log_head.close();
            
            string branch_(current_branch);
            string LOG_branch_path= LOG_PATH+branch_;
            
             //writing in git/logs/refs/current_branch
            ofstream branch_head;
            branch_head.open(LOG_branch_path,ofstream::app);
            branch_head<<merge_log_content<<'\n';
            branch_head.close();
        }
    }
    
    else{
        //if branch doesnt exist
        cout<<"Error: "<<branch_name<<" branch doesn't exists"<<endl;
    }
}