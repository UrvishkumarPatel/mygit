/* object defination of:
    - commit
    - blob
        - hash_object
        - compress the new content
        -
    - tree
and helper classes and definations
*/




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



int add(string file_name){
    string content="";
    string line;
    ifstream myfile(file_name);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            cout<<line<<endl;
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
    // mkdir(path,"0777");

    // read content
    // content= ;
    // hash-object
    // sha1= hash_object(content, "blob");
    //path and mkdir

    // compress

    // write

    return 0;
}