/* implement commit here */

/*
form a tree
-backtrack it to compute the hash of all the obejcts
    - if it does exist, does not matter just recompute it.
- create new commit object
- get the previous commit object and save it to the new commit object as parent
- save the sha1 of the new commit object to .git/objects/refs/head

*/
#include <vector>
// #include "object.h" //mysplit
#include <bits/stdc++.h>

#define PATH_INDEX "git/index"
#define ROOT_PATH "."
#define MAX_FILE_NAME_LENGTH 1024


using namespace std;

class treeNode{

    public:
        string mode;

        // vector<string> ref_objects_type; // list of object names
        // vector<string> ref_objects_sha;
        // vector<string> ref_objects_name;
        string sha;
        string type;
        string name;
        vector<treeNode> pointers;
};



class commit{
    public:
        string author;
        string commiter;
        string sha1;
        treeNode root;
        vector<commit> parent_commit;
        //etc
};

	// char **args = malloc(tok_nos * sizeof(char*));
	// int i = 0;



char** split_index_line(char* line_){
    // char line_[MAX_FILE_NAME_LENGTH];
    // strcpy(line_, line.c_str());

    char** tokens= (char**)malloc(4*sizeof(char*));
    int k=0;

    char* token = strtok(line_, " ");
    while (token != NULL){
        tokens[k]= token;
        token = strtok(NULL, " ");
        k+=1;
    }
    tokens[k]=NULL;
    return tokens;  // check this
}

// class Graph
// {
//     int V;    // No. of vertices

//     // Pointer to an array containing
//     // adjacency lists
//     list<int> *adj;

//     // A recursive function used by DFS
//     void DFSUtil(int v, bool visited[]);
// public:
//     Graph(int V);   // Constructor

//     // function to add an edge to graph
//     void addEdge(int v, int w);

//     // DFS traversal of the vertices
//     // reachable from v
//     void DFS(int v);
// };
class tree{
    public:
      tree(){
        treeNode root;
        root.name= "root";
        root.type = "tree";
        map<string, treeNode> hashSet;
        hashSet[ROOT_PATH]=root;
        }
        treeNode root; //"."
        map<string, treeNode> hashSet;

        void build_tree(string path_, char** blob_data){
            /* call strtok each time and check if the node with that name exists
                if yes then verify type also
                if not then make the node
            */
            //    a.txt
            // temp points to root

            // loop over childrens of temp:
                // if a exists: (check for name(must be a) and type(must be tree))
                //  temp = a
                // else:
                //  create node a (define type as tree, name as a, mode appropriately, sha null, no pointers yet)
            // []->[]->[]->[]
            // a/b/c.txt
            // a/b.txt

            string present_path= ROOT_PATH;
            treeNode iterator= root;
            char* token;
            char path[MAX_FILE_NAME_LENGTH];
            strcpy(path,path_.c_str());
            int type_file;

            token=strtok(path,"/");
            string token_(token);
            present_path= present_path+"/"+token_;
            char present_path_[MAX_FILE_NAME_LENGTH];
            strcpy(present_path_,present_path.c_str());

            while (token!=NULL){

                type_file=isDir(present_path_);
                if (hashSet.find(present_path) != hashSet.end()){
                    iterator.pointers.push_back(hashSet[present_path]);
                    iterator= hashSet[present_path];
                }
                else{
                    treeNode newTree;
                    newTree.name= token_;
                    newTree.mode= blob_data[1];

                    if(type_file==1){
                        /* create tree node */
                        newTree.type= "tree";
                        iterator.pointers.push_back(newTree);
                        hashSet[present_path]= newTree;
                        iterator= newTree;
                    }
                    else if(type_file==2){
                        /* create blob object */
                        newTree.type= "blob";
                        string blob_data_(blob_data[1]);

                        newTree.sha= blob_data_;
                        iterator.pointers.push_back(newTree);
                        hashSet[present_path]=newTree;
                        iterator=newTree;
                        break;
                    }


                }
                token= strtok(NULL, "/");
                string token_(token);
                present_path= present_path+"/"+token_;
                present_path_[MAX_FILE_NAME_LENGTH];
                strcpy(present_path_,present_path.c_str());
            }
        }

        void print_tree(){
            for(auto x: hashSet){
                cout<<x.first<<"    "<< x.second.type<< endl;
            }
        }

        void compute_hash(/*treeNode root*/){
            // use root node and index files to compute hash
            // write each object to .git/objects

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
                    char** blob_data= split_index_line(line_);
                    build_tree(curPath, blob_data);
                    // cout<<blob_data[0]<<blob_data[1]<< blob_data[2]<< endl;

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



void run_commit(string flag, string message){

    if (flag!= "-m"){
        cout<< "not supported!"<<endl;
        exit(1);
    }
    else{
        // read index file and build the tree
        // compute the hash
        tree myTree;
        myTree.read_index();
        commit commit_obj;
        commit_obj.root= myTree.root;
        myTree.print_tree();
        // (root.ref_objects_sha)
        // create commit object
        // update head
        // if isDir(head_path)==0{

        // }
    }




}




void commit(int argc, char* argv[]){
   if(argc==2){
        printf("No arguments given\n");
        exit(1);
    }
    else{
        string file_name=argv[2];
        run_commit("-m", "first commit");
        cout<< "some print"<<endl;
    }
}


