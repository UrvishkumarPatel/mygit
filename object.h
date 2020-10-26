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
    printf("Uncompressed string is: %s\n", a);
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
    cout<<path<<endl;
    string pathDir=".git/objects/"+sha1.substr(0,2);
    int len=content.length(); //length of content
    const string store_content = "blob " +to_string(len)+'\0'+content;
    cout<<path<<endl;
    //create new blob
    // char pathname[256];
    // strcpy(pathname, pathDir.c_str());
    // cout <<pathname<< endl;
    // mkdir(pathname,0777);
    // cout<<path<<endl;
    // compress the store
    const string compressed_store= compress(store_content,len);
    cout << compressed_store << endl;
    // cout << "x\x9sCK\xCA\xC9OR04c(\xCFH,Q\xC8,V(-\xD0QH\xC9O\xB6\a\x00_\x1C\a\x9D" <<endl;

    // string p="t.txt";
    ofstream fout;
    fout.open(path);
    int i=0;
    while (i<compressed_store.length()-1){
        fout.put(compressed_store[i]);
        cout << compressed_store[i];
        i++;
    }
    cout<<"" <<endl;
    fout.close();


    // string original_content= decompress(compressed_store, len+store_content.length());
    // // cout << original_content<<endl;
    // int k=0;
    // while (k<len+store_content.length()){
    //     cout<< original_content[k];
    //     k++;
    // }
    // cout <<endl;

    return 0;
}