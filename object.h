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
        // read content
        // content= ;
        // hash-object
        // sha1= hash_object(content, "blob");
        //path and mkdir

        // compress

        // write

        return 0;
    }