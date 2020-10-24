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
using namespace std;

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





 string compress(string store_content){
    char a[5000];
    strcpy(a, store_content.c_str());
    char compressed_store[5000];
    // compress a into compressed_store

    // zlib struct
    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;
    // setup "a" as the input and "compressed_store" as the compressed output
    defstream.avail_in = (uInt)strlen(a)+1; // size of input, string + terminator
    defstream.next_in = (Bytef *)a; // input char array
    defstream.avail_out = (uInt)sizeof(compressed_store); // size of output
    defstream.next_out = (Bytef *)compressed_store; // output char array

    // the actual compression work.
    deflateInit(&defstream, Z_BEST_COMPRESSION);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);

    // This is one way of getting the size of the output
    // printf("Compressed size is: %lu\n", strlen(b));
    // printf("Compressed string is: %s\n", b);
    // std::cout <<"x\x9CK\xCA\xC9OR04c(\xCFH,Q\xC8,V(-\xD0QH\xC9O\xB6\a\x00_\x1C\a\x9D"<<"\n" << b<< std::endl;
    // char k[5000]= "x\x9CK\xCA\xC9OR04c(\xCFH,Q\xC8,V(-\xD0QH\xC9O\xB6\a\x00_\x1C\a\x9D";
     return compressed_store;
 }



int add(string file_name){
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
    string path=".git/objects/"+sha1.substr(0,2)+"/"+sha1.substr(2,38);
    const string store_content = "blob " + std::to_string(content.length())+"\\0";

    cout<<path<<endl;
    //create new blob
    // mkdir(path,"0777");

    // compress the store
    const string compressed_store= compress(store_content);
    cout << compressed_store <<endl;

    // write compressed store
    // ofstream my;
    // my.open ("l.txt");   //change to path
    // my << compressed_store ;
    // my.close();

    return 0;
}