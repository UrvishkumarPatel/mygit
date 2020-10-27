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


string compress(string store_content, int len){
    char a[5000];
    // strcpy(a, store_content.c_str());
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
    char compressed_store[5000];
    // printf("bl string is: %s\n", a);
    // zlib struct
    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;

    int totallen= k; // lenght of header+content
    defstream.avail_in = (uInt)totallen; // size of input, string + terminator
    defstream.next_in = (Bytef *)a; // input char arraylen
    defstream.avail_out = (uInt)sizeof(compressed_store); // size of output
    defstream.next_out = (Bytef *)compressed_store; // output char array

    // the actual compression work.
    deflateInit(&defstream, Z_BEST_COMPRESSION);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);
    return compressed_store;
}


// buggy!
// string decompress(string compressed_content, int lenCompressed)
// {
//     // char b[5000];
//     char c[5000];  //for decompression

//     char a[5000];
//     strcpy(a, compressed_content.c_str());

//     // STEP 2.
//     // inflate b into c
//     // zlib struct
//     z_stream infstream;
//     infstream.zalloc = Z_NULL;
//     infstream.zfree = Z_NULL;
//     infstream.opaque = Z_NULL;
//     // setup "b" as the input and "c" as the compressed output
//     infstream.avail_in = (uInt)((char*)(Bytef *)a - a); // size of input
//     infstream.next_in = (Bytef *)a; // input char array
//     infstream.avail_out = (uInt)sizeof(c); // size of output
//     infstream.next_out = (Bytef *)c; // output char array

//     // the actual DE-compression work.
//     inflateInit(&infstream);
//     inflate(&infstream, Z_NO_FLUSH);
//     inflateEnd(&infstream);

//     printf("Uncompressed size is: %lu\n", strlen(c));
//     printf("Uncompressed string is: %s\n", c);
//     // std::cout<< lenCompressed<<std::endl;
//     int k=0;
//     while (k<lenCompressed){
//         cout<< c[k];
//         k++;
//     }
//     cout << "asdasdsad" << endl;
//     return c;
// }

/* return the type of PATH */




// // - write commit object
// // - write tree object
// def commit_():
//     // build tree using blobMetaData
//     // create commit object
//     // add refference to root of tree built, parent commits



int decimaltoOctal(int deciNum)
{

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
    string path= GIT_DIR+"/objects/"+sha1.substr(0,2)+"/"+sha1.substr(2,38);
    // cout<<path<<endl;
    string pathDir=GIT_DIR+"/objects/"+sha1.substr(0,2);
    int len=content.length(); //length of content
    const string store_content = "blob " +to_string(len)+'\0'+content;
    // cout<<"creating blob for  " << file_name<< " " <<path<<endl;
    //create new blob
    char dirPath[MAX_FILE_NAME_LENGTH];
    strcpy(dirPath, pathDir.c_str());
    mkdir(dirPath,0777);
    // cout<<dirPath<<endl;
    // compress the store
    const string compressed_store= compress(store_content,len);
    // cout << compressed_store << endl;
    // cout << "x\x9sCK\xCA\xC9OR04c(\xCFH,Q\xC8,V(-\xD0QH\xC9O\xB6\a\x00_\x1C\a\x9D" <<endl;

    // update file
    updateIndexFile(sha1, file_name);


    // write compressed content
    // string p="t.txt";
    ofstream fout;
    fout.open(path);
    int i=0;
    while (i<compressed_store.length()-1){
        fout.put(compressed_store[i]);
        // cout << compressed_store[i]<<endl;
        i++;
    }
    // cout<<"\n" <<endl;
    fout.close();

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