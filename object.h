/* object defination of:
    - commit
    - blob
        - hash_object
        - compress the new content
        -
    - tree
and helper classes and definations

note: zlib compression and decompression taken from  - https://gist.github.com/arq5x/5315739#file-zlib-example-cpp-L7 8
store = header + data
*/



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


#define MAX_FILE_NAME_LENGTH 1024
#define PATH_INDEX "git/index"
#define git_dir "git"
#define UPPER_BOUND 2147483647
#define SIZE_STORE  "git/size_store"
// #define PATH_INDEX "p.txt"
string GIT_DIR(git_dir);

void add_run(string location);

string hash_object(string content, string type){
    /*
    type : blob, commit, tree
    */
    const string header = type + " " + std::to_string(content.length())+'\0';
    SHA1 checksum;
    const string store= header+content;
    // cout << store << endl;
    checksum.update(store);
    const string hash = checksum.final();
    // cout << hash.substr(0,2) << endl;

    return hash;
}


int GetMaxCompressedLen( int nLenSrc){  
    int n16kBlocks = (nLenSrc+16383) / 16384; // round up any fraction of a block
    return ( nLenSrc + 6 + (n16kBlocks*5) );
}
// x= (y+k)/k+1
// alpha= y+6+(((y+k)/k+1)*5)


auto compress(string store_content, int len){
    //len= type + size + 1 ("\0") + content size
    char* a=(char *)malloc((len)*sizeof(char));   //dynamically allocate
    int k=0;
    while (store_content[k]!='\0'){
        a[k]= store_content[k];
        k++;
    }
    a[k]= '\0';
    k+=1;
    while (store_content[k]!='\0'){
        a[k]= store_content[k];
        k++;
    }
    int max_compress_len = GetMaxCompressedLen(len);
    // cout<<max_compress_len<<endl;
    char* compressed_store=(char *)malloc((max_compress_len)*sizeof(char));   //change this
    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;

    int totallen= k; // lenght of header+content
    defstream.avail_in = (uInt)totallen; // size of input, string + terminator
    defstream.next_in = (Bytef *)a; // input char arraylen
    defstream.avail_out = (uInt)max_compress_len; // size of output
    defstream.next_out = (Bytef *)compressed_store; // output char array

    // the actual compression work.
    deflateInit(&defstream, Z_BEST_COMPRESSION);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);

    pair<char*, int> compressed_info;
    compressed_info.first= compressed_store;
    compressed_info.second= defstream.total_out;

    return compressed_info;
}


int decimaltoOctal(int deciNum){

    // initializations
    int octalNum = 0, countval = 1;
    int dNo = deciNum;

    while (deciNum != 0) {

        // decimals remainder is calculated
        int remainder = deciNum % 8;

        // storing the octalvalue
        octalNum += remainder * countval;

        // storing exponential value
        countval = countval * 10;
        deciNum /= 8;
    }
    // cout << octalNum << endl;
    return octalNum;
}

string mysplit(string inLine){
    char line[MAX_FILE_NAME_LENGTH];
    strcpy(line, inLine.c_str());
    char* tokens[4];
    int k=0;

    char* token = strtok(line, " ");
    while (token != NULL){
        tokens[k]= token;
        token = strtok(NULL, " ");
        k+=1;
    }
    string curPath(tokens[k-1]);
    return curPath;
}


void update_size_store(string sha1,int secret_code,int store_len){
    // update store size
    string line;
    int isPresent= 0;
    ofstream fout_3;
    if(isDir((char *)SIZE_STORE)==0){        
          fout_3.open(SIZE_STORE);
          fout_3.close();
    }
    
    const string content= sha1+ " "+ to_string(secret_code)+ " "+ to_string(store_len);
    ifstream size_store(SIZE_STORE);
    if(size_store.is_open()){
        while(getline(size_store, line)){
            // cout << line.comconontentpare(content)<< " "<<line<<" "<< content<<endl;
            if (line.compare(content)==0){ // 
                isPresent= 1;
                break;
            }
        }
        size_store.close();
    }
    else{
        cout<<"Error"<<endl;
        exit(0);
    }

    if(!isPresent){
        ofstream fout_size;
        fout_size.open(SIZE_STORE, ios::app);
        fout_size << content;
        fout_size<<"\n";
        fout_size.close();
    }
}

void updateIndexFile(string sha, string pathname){
    // get the file permissions

    int isPresent=1;
    const char* path= pathname.c_str();
    struct stat fb;
    if (stat(path, &fb)==-1){ // 0 when file exist
        // printf("cannot stat on %s location!\n", PATH);  //are you planning to print this?
        isPresent= 0; // is not present in working dir
    }
    if (isPresent){
        unsigned long var= (unsigned long)fb.st_mode;

        int mode= decimaltoOctal(var);
        string identifier= to_string(mode) + " "+ sha + " " + to_string(0) + " "+ pathname ;

        string line;
        // read file content
        ifstream myfile(PATH_INDEX);
        if(myfile.is_open()){
            while(getline(myfile,line)){
                if (line.compare(identifier)==0){
                    return;
                }
            }
            myfile.close();
        }
        else{
            cout<<"Error"<<endl;
            exit(0);
        }

        // write to the index file
        fstream f;
        f.open(PATH_INDEX, fstream::out | fstream::app);
        f << identifier<<endl;
        f.close();
    }
    else{
        string line;
        string content="";
        // read file content
        ifstream myfile(PATH_INDEX);
        if(myfile.is_open()){
            while(getline(myfile, line)){
                string curPath= mysplit(line);
                if (curPath.compare(pathname)){
                    content+=line;
                }
            }
            myfile.close();
        }
        else{
            cout<<"Error"<<endl;
            exit(0);
        }
        ofstream f;
        f.open(PATH_INDEX, ofstream::trunc);
        f << content;
        f.close();
    }
}

void blobDir(char* dirname){
    /* creates a blob for all the files present in this directory. */
    DIR* dir = opendir(dirname); // open the directory location to read.

    if (dir == NULL){
        // handelling error
        fprintf(stderr, "opendir: '%s': %s\n", dirname, strerror(errno));
        return;
    }

    struct dirent* dir_reader; // to read the directory
    char newlocation[MAX_FILE_NAME_LENGTH] = "";
    while ((dir_reader = readdir(dir)) !=NULL){
        if ((!strcmp(dir_reader->d_name, ".")) || (!strcmp(dir_reader->d_name, ".."))){
            // ignore "." and ".." directories
        }
        else{
            strcpy(newlocation, dirname);
            strcat(newlocation, "/");
            strncat(newlocation, dir_reader->d_name, strlen(dir_reader->d_name));
            // query to blob the directory file/ subdirectory
            string newLocation(newlocation);
            add_run(newLocation);
        }
    }
    closedir(dir);
}


char* decompress(string compress_string, int secret_code,int len){
    /* perfectly working!*/
    //secret code .. dunno what it does but very important
    // size of the input
    int size_input= len; // 32768
    char* c;
    c=(char*)malloc(size_input*sizeof(char));
    // cout<<sizeof(c)<<endl;
    char b[size_input]; // compressed string
    strcpy(b, compress_string.c_str());

    // zlib struct;
    z_stream infstream;
    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;
    infstream.avail_in = (uInt)secret_code; // size of input

    infstream.next_in = (Bytef *)b; // input char array
    infstream.avail_out = (uInt)secret_code; // size of output
    infstream.next_out = (Bytef *)c; // output char array
     
    inflateInit(&infstream);
    inflate(&infstream, Z_NO_FLUSH);
    inflateEnd(&infstream);
    // int i=0;
    // while (i!=20){
    //     cout<<c[i];
    //     i++;
    // }
    // cout<<endl;

    return c;
}


auto get_compressed_store_data(string sha){
    string line;
    ifstream size_store(SIZE_STORE);
    int flag=0;
    pair<int,int> compressed_store_data;
    if(size_store.is_open()){
        while(getline(size_store, line)){
            char line_[MAX_FILE_NAME_LENGTH];
            strcpy(line_, line.c_str());
            char** data=split_index_line(line_," ");
            // cout<< data[0]<<" "<<data[1]<<" "<<data[2]<<endl;
            string sha1(data[0]);
            if (sha1.compare(sha)==0){ // 
                flag=1;
                compressed_store_data.first=atoi(data[1]);
                compressed_store_data.second=atoi(data[2]);
                return compressed_store_data;
            }
        }
        size_store.close();
    }
    else{
        cout<<"Error"<<endl;
        exit(0);
    }
    if(flag==0){
        cout<<"No matching sha found"<<endl;
        exit(0);
    }
    return compressed_store_data;
}
// char** split_index_line(char* line_, string delimiter_){


void print_string(char* str, int store_len){
    /* prints the string. Deals with "/0" */
    int indx=0;
    while (indx!=store_len){
        cout<< str[indx];
        indx++;
    }
    cout<< endl;
}

char** return_split_content_from_sha(string sha){
    // get secret code and size from indexfile (SIZE_STORE)
    // decompress 
    // simply return
    string content;
    string path= GIT_DIR+"/objects/"+sha.substr(0,2)+"/"+sha.substr(2,38);
    // string path= ".git/objects/b5/22cff36efe4c57d1e3b1977531fa0dca7f5842";
    // const char* path= "/home/ac-optimus/implement_git/copy_sha";
    // cout<<"before reading"<<path<<endl;
    ifstream f_reader(path);
    getline (f_reader, content); // compressed data in content
    pair<int, int> compressed_data= get_compressed_store_data(sha); //secret code, size_store
    cout<<"content of path  "<< compressed_data.first<< " "<< compressed_data.second<<" "<< content<< " " << endl;

    char* decompress_string= decompress(content, compressed_data.first, compressed_data.second);
    print_string(decompress_string, compressed_data.second);
    // split based on "\n"
    char** lines= split_index_line(decompress_string, "\n");
    return lines;
}

void write_object(string sha1, string content, string type){
    string path= GIT_DIR+"/objects/"+sha1.substr(0,2)+"/"+sha1.substr(2,38);
    // cout<<path<<endl;
    string pathDir=GIT_DIR+"/objects/"+sha1.substr(0,2);
    int len=content.length(); //length of content
    const string header= type +to_string(len);
    const string store_content = header+'\0'+content;
    cout<< store_content<< endl;    
    int store_len= header.length() +len+1 ;
    // cout<<"creating blob for  " << file_name<< " " <<path<<endl;
    //create new blob
    char dirPath[MAX_FILE_NAME_LENGTH];
    strcpy(dirPath, pathDir.c_str());
    mkdir(dirPath,0777);
    // cout<<dirPath<<endl;
    // compress the store
    pair<char*, int> compressed_store_= compress(store_content, store_len);
    cout<< compressed_store_.first<< " " << compressed_store_.second<< endl;
    char* compressed_store= compressed_store_.first;
    // cout << compressed_store << endl;
    // cout << "x\x9sCK\xCA\xC9OR04c(\xCFH,Q\xC8,V(-\xD0QH\xC9O\xB6\a\x00_\x1C\a\x9D" <<endl;
    // char* decompress_string= decompress(compressed_store, compressed_store_.second, store_len);
    // print_string(decompress_string, store_len);
    // write compressed content
    // string p="t.txt";
    // cout<<"before printing decompress!! "<<path<< endl;
    char Path[MAX_FILE_NAME_LENGTH];
    strcpy(Path, path.c_str());
    cout<< "writing at- "<<path<<endl;
    // char sentence[1000];
    // ofstream fptr;
    // fptr.open(path ,ios::app);
    // string p=store_content+"\n";
    // fptr<<p;
    // fptr.close();
    FILE *fptr;
    fptr = fopen(Path, "w");

    if (fptr == NULL) {;
    // print_string(decompress_string, stor
        printf("Error!");
        exit(1);
    }
    // printf("Enter a sentence:\n");
    // fgets(sentence, sizeof(sentence), );
    fprintf(fptr, "%s", compressed_store);
    fclose(fptr);
    // ofstream fout;
    // fout.open(path);
    // int i=0;
    // // while (i<compressed_store.length()-1){
    //     while (i< strlen(compressed_store)-1){
    //     fout.put(compressed_store[i]);
    //     // cout << compressed_store[i]<<endl;
    //     i++;
    // }
    string content1;
    ifstream f_reader(path);
    getline (f_reader, content1); // compressed data in content
    // cout<<"content of path  "<<content1<< " " << compressed_store_.second<< " "<< store_len<< endl;
    char* decompress_string1;
    for (int i =0; i<4; i++){
        // cout<<"content "<<i<<" "<<content1<<endl;
        decompress_string1= decompress(content1, compressed_store_.second, store_len);
        print_string(decompress_string1, store_len);
    }
    // cout<< "-------compressed content written-------"<<compressed_store<< endl;
    // char* decompress_string= decompress(compressed_store, compressed_store_.second, store_len);
    // print_string(decompress_string, store_len);


    // cout<<"\n" <<endl;
    // fout.close();
    // update the store data
    // cout<< "updating update store with-- "<< compressed_store_.second << store_len<< endl;
    update_size_store(sha1, compressed_store_.second, store_len);
    // pair<int,int> get1;
    // get1 = get_compressed_store_data(sha1);
    // cout<<get1.first<<" "<<get1.second<<endl;
}


void createBlob(string file_name){
    /* create a blob for given file*/
    string content="";
    string line;
    // read file content
    ifstream myfile(file_name);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            // cout<<line<<endl;
            content+=line;
        }
        myfile.close();
    }
    else{
        cout<<"Error"<<endl;
    }
    string sha1=hash_object(content,"blob");

    write_object(sha1, content, "blob");
    // update file
    updateIndexFile(sha1, file_name);

}

void add_run(string location){
    /*
    checks  if location is file -- create a blob
            if directory then first look for the files and create blob for all of them
    */
    char location_new[MAX_FILE_NAME_LENGTH];
    strcpy(location_new, location.c_str());
    int status = isDir(location_new); // location is file or directory

    if (status == 2){
        //location is file;
        createBlob(location);
    }
    else if (status == 1){
        // location is directory
        blobDir(location_new);
    }
    else{
        updateIndexFile("", location);
    }
}

void add(int argc,char* argv[]){
    if(argc==2){
        printf("No arguments given\n");
        exit(1);
    }
    else{
        string file_name=argv[2];
        add_run(file_name);
    }
}