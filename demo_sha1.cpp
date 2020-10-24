/*
    demo_sha1.cpp - demo program of
 
    ============
    SHA-1 in C++
    ============
 
    100% Public Domain.
 
    Original C Code
        -- Steve Reid <steve@edmweb.com>
    Small changes to fit into bglibs
        -- Bruce Guenter <bruce@untroubled.org>
    Translation to simpler C++ Code
        -- Volker Diels-Grabsch <v@njh.eu>
*/

#include "sha1.hpp"
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;

int main(int /* argc */, const char ** /* argv */)
{
    // for "what is up, doc?"
    const string content= "what is up, doc?";
   // int size_content= std
    const string header = "blob "+ std::to_string(content.length())+'\0';
//    cout << content.length() << endl;
    SHA1 checksum;
//    checksum.update(header);
  //  const string hash = checksum.final();

//    cout << "The SHA-1 of \"" << header << "\" is: " << hash << endl;
    const string store= header+content;
    cout << store << endl;
    checksum.update(store);
    const string hash = checksum.final();
    cout << hash << endl;
    return 0;
}
