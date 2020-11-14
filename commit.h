/* implement commit here */

/*
form a tree
-backtrack it to compute the hash of all the obejcts
    - if it does exist, does not matter just recompute it.
- create new commit object
- get the previous commit object and save it to the new commit object as parent
- save the sha1 of the new commit object to .git/objects/refs/head

*/
// #include <vector>
// // #include "object.h" //mysplit
// #include <bits/stdc++.h>

// #define PATH_INDEX "git/index"
// #define ROOT_PATH "."
// #define MAX_FILE_NAME_LENGTH 1024
// // #define PATH "git/refs/heads/master"
// # define HEAD_PATH "git/HEAD"
// # define GIT_PATH "git/"


// using namespace std;

string PARENT_SHA="";

class treeNode{

    public:
        string mode;

        // vector<string> ref_objects_type; // list of object names
        // vector<string> ref_objects_sha;
        // vector<string> ref_objects_name;
        string sha="";
        string type;
        string name;
        vector<treeNode> pointers;
        vector<string> childpaths;


        void print_attributes(){
            cout<<"mode: "<< mode <<endl;
            cout<<"type: "<< type <<endl;
            cout<<"sha: "<< sha <<endl;
            cout<<"name: "<< name <<endl;
            cout<<"-----------------"<<endl;

        }
};



class commit{
    public:
        string author;
        string commiter;
        string sha1;
        string root_sha;
        vector<string> parent_commit;
        //etc
};

	// char **args = malloc(tok_nos * sizeof(char*));
	// int i = 0;



// char** split_index_line(char* line_, string delimiter_){
//     char delimiter[MAX_FILE_NAME_LENGTH];
//     strcpy(delimiter, delimiter_.c_str());

//     char** tokens= (char**)malloc(4*sizeof(char*));
//     int k=0;

//     char* token = strtok(line_, delimiter);
//     while (token != NULL){
//         tokens[k]= token;
//         token = strtok(NULL, delimiter);
//         k+=1;
//     }
//     tokens[k]=NULL;
//     return tokens;  // check this
// }


class tree{
    public:
        treeNode root; //"."
        map<string, treeNode*> hashSet;

      tree(){

        root.name= "root";
        root.type = "tree";
        hashSet[ROOT_PATH]=&root;
        }

        void build_tree(string path_, char** blob_data){

            // 0- MODE
            // 1- SHA
            // 2- STAGE
            // 3- path
            string present_path= ROOT_PATH;

            treeNode* iterator= &root;
            char* token;
            char path[MAX_FILE_NAME_LENGTH];
            strcpy(path, path_.c_str());
            int type_file;

            token=strtok(path,"/");

            while (token!=NULL){

                string token_(token);
                present_path= present_path+"/"+token_;
                char present_path_[MAX_FILE_NAME_LENGTH];
                strcpy(present_path_,present_path.c_str());


                type_file=isDir(present_path_);
                if (hashSet.find(present_path) != hashSet.end()){ //is present
                    iterator->pointers.push_back(*hashSet[present_path]);
                    iterator= hashSet[present_path];
                }
                else{
                    // treeNode newTree; //todo reinitialization issue
                    treeNode* newTree= new treeNode;
                    newTree->name= token_;

                    if(type_file==1){  // directory
                        /* create tree node */
                        newTree->mode= "040000";
                        newTree->type= "tree";
                        iterator->pointers.push_back(*newTree);
                        iterator->childpaths.push_back(present_path);
                        hashSet[present_path]= newTree;
                        iterator= newTree;


                    }
                    // else if(type_file==2){  // file
                    else{
                        /* create blob object */
                        newTree->mode= blob_data[0];
                        newTree->type= "blob";
                        string blob_data_(blob_data[1]);
                        newTree->sha= blob_data_;
                        iterator->pointers.push_back(*newTree);
                        iterator->childpaths.push_back(present_path);
                        hashSet[present_path]=newTree;
                        break;
                    }
                }

                token= strtok(NULL, "/");
                // cout<<iterator->name<<" after update and else "<<endl;


                // cout<<"   adsfsadf"<<endl;
                // string token_(token);
                // present_path= present_path+"/"+token_;
                // present_path_[MAX_FILE_NAME_LENGTH];
                // strcpy(present_path_,present_path.c_str());
            }
            // ;
            // cout<<"   "<<endl;
            // cout<<iterator->name<< " ignore"<<endl;


            // dfs(root);
            // print_hash();
        }

        void print_hash(){
            for(auto x: hashSet){
                cout<< x.first<<endl;
                if (x.second->type!="blob"){
                    x.second->pointers[0].print_attributes();
                    if (x.second->name=="demo"){
                        x.second->pointers[1].print_attributes();
                    }
                }
            cout<<" --- done --- "<<endl;

            }
        }



        string dfs(treeNode curNode){
            // curNode.print_attributes();
            // when leaf content
            if (curNode.type=="blob"){
                return curNode.mode+" "+ "blob" + " "+ curNode.sha+ " "+ curNode.name;
            }


            // craeate object
            string content;
            for (auto ptr = curNode.childpaths.begin(); ptr <curNode.childpaths.end(); ptr++){
                content += dfs(*hashSet[*ptr]);
                if (ptr!= curNode.childpaths.end()-1)
                    content += "\n";
            }

            // cout<<"content of -- "<<curNode.name<<"\n"<< content<<"\n----------------" <<endl;
            // exit();
            // pass content to compute hash function
            curNode.sha= hash_object(content, curNode.type);
            // compress
            // make and write file
            write_object(curNode.sha, content, "tree");
            // fstream f;
            // f.open("p.txt", fstream::out | fstream::app);
            // f << content<<endl;
            // f.close();
            // cout<<"upar"<<endl;
            cout << curNode.mode+" "+ "tree" + " "+ curNode.sha+  " "+ curNode.name << endl;
            // cout<<"niche"<<endl;
            return curNode.mode+" "+ "tree" + " "+ curNode.sha+  " "+ curNode.name;
            // return curNode.mode+" "+ curNode.name +"\0" + curNode.sha;

        }



        void read_index(){
            // read index file line by line
            string line;
            // read file content
            ifstream myfile(PATH_INDEX);
            if(myfile.is_open()){
                while(getline(myfile, line)){
                    // 100644 e69de29bb2d1d6434b8b29ae775ad8c2e48c5391 0       asjdk.txt

                    string curPath= mysplit(line);
                    char line_[MAX_FILE_NAME_LENGTH];
                    strcpy(line_, line.c_str());
                    // char delimiter_[MAX_FILE_NAME_LENGTH];
                    // strcpy(delimiter, delimiter_.c_str());
                    
                    // char space[]= " ";
                    char** blob_data= split_index_line(line_, " ");
                    build_tree(curPath, blob_data);

                }
                myfile.close();
            }
            else{
                cout<<"Error"<<endl;
                exit(1);
        }


    }
};

// blob object is the created file itself, instance of the object present physically

string get_content_merge_commit(string root_sha, string commit_msg, string parent_1, string parent_2){
    string author= "imp_git";
    string commiter= "imp_git";
    string parent_content= "parent "+parent_1+"\nparent "+parent_2+"\n";
    string content= "tree "+root_sha + "\n"+ parent_content+"author "+ author + "\n" + "committer "+commiter+"\n\n"+ commit_msg;
    return content;
}

string get_content_commit(string root_sha, string commit_msg){
    /* TODO- adding parent pointers */
    // char PATH_[MAX_FILE_NAME_LENGTH];
    // strcpy(PATH_, PATH.c_str());
    string parent_content="";
    // loop over all the parents
    char* PATH_= get_cur_head();
    cout<<"\n"<<PATH_<<" is the get_cur_head()"<<endl;
    string path(PATH_);
    char ref_path[MAX_FILE_NAME_LENGTH];
    strcpy(ref_path, GIT_PATH);
    strcat(ref_path, PATH_);
    if (isDir(ref_path)==2){  //2 -- PATH is a regular file
        // create a new file at ref
        parent_content+="parent ";
        string ref_path_(ref_path);
        ifstream myfile(ref_path_);
        if(myfile.is_open()){
            while(getline(myfile,PARENT_SHA)){
                cout<<PARENT_SHA<<" is the parent sha"<<endl;
            }
            myfile.close();
        }
        else{
            cout<<"Error"<<endl;
            // exit();
        }
        parent_content+= PARENT_SHA+"\n";
    }
    string author= "imp_git";
    string commiter= "imp_git";
    // vector<string> parent_commit;  # get the parent sha from ref/heads

    string content= "tree "+root_sha + "\n"+ parent_content+"author "+ author + "\n" + "committer "+commiter+"\n\n"+ commit_msg;
    return content;
}



void run_commit(string message, int merge_flag=0, string parent_1="", string parent_2=""){

    // read index file and build the tree
    // compute the hash
    tree myTree;
    myTree.read_index();
    
    string root_content = myTree.dfs(myTree.root);

    char root_content_[MAX_FILE_NAME_LENGTH];
    strcpy(root_content_, root_content.c_str());
    char** tokens_root_hash_= split_index_line(root_content_, " ");
    // char** tokens_root_hash= split_index_line(tokens_root_hash_[1], "\t");
    // cout<<tokens_root_hash[0]<<endl;
    string root_sha(tokens_root_hash_[1]);
    string commit_sha;
    string commit_content;

    if (merge_flag){
        commit_content= get_content_merge_commit(root_sha, message, parent_1, parent_2);
        commit_sha=hash_object(commit_content,"commit");

    }
    else{
        commit_content= get_content_commit(root_sha, message);
        commit_sha=hash_object(commit_content,"commit");

        if (PARENT_SHA.compare("")!=0){
            vector<string> entries= return_split_content_from_sha(PARENT_SHA);
            // split entries[0] and get sha
            // char** split_index_line(char * line_, string delimiter_,  int * n=&DEFAULT){
            char entries_[MAX_FILE_NAME_LENGTH];
            strcpy(entries_, entries[0].c_str());
            
            // char first_line[MAX_FILE_NAME_LENGTH];
            // strcpy(first_line, entries_);
            char** splitted_line= split_index_line(entries_," ");
            char* tree_sha=splitted_line[1];
            string tree_sha_(tree_sha);
            // cout <<"----------"<<endl;
            // cout<<tree_sha_<<"\n"<<root_sha<<endl;
            // cout <<"----------"<<endl;
            if (tree_sha_.compare(root_sha)==0){
                cout<<"Nothing to commit."<<endl;
                return;
            }
        }
    }

    /* tree 9b5a3d2570f0b61a9aca5188cc4e33c3a0b3f84b
        author imp_git
        committer imp_git

        first commit
    */

    write_object(commit_sha, commit_content, "commit");
    // overwrite commit at head ////////
    char* path_= get_cur_head();
    string PATH(path_);
    // ofstream MyFile("git/"+PATH);
    // MyFile << commit_sha;
    // MyFile.close();
    ofstream f;
    f.open("git/"+PATH);
    f << commit_sha;
    f.close();

    //definining commit log content
    string log_content;
    log_content+=commit_sha+" imp_git imp_git commit : "+message;

    //writing in git/logs/HEAD
    ofstream log_head;
    log_head.open(LOG_HEAD_PATH,ofstream::app);
    log_head<<log_content<<'\n';
    log_head.close();

    //writing in git/logs/refs/current_branch

    //get current branch name
    char current_branch[MAX_FILE_NAME_LENGTH];
    get_cur_branch_name(current_branch);
    string branch_(current_branch);
    string LOG_branch_path= LOG_PATH+branch_;

    ofstream branch_head;
    branch_head.open(LOG_branch_path,ofstream::app);
    branch_head<<log_content<<'\n';
    branch_head.close();

}


void commit(int argc, char* argv[]){
   if(argc==2){
        printf("No arguments given\n");
        exit(1);
    }
    else{
        string flag(argv[2]);
        if (flag!= "-m"){
            cout<< "not supported!"<<endl;
            exit(1);
        }
        else{
            run_commit(argv[3]);
            cout<< "some print"<<endl;
        }
    }
}


