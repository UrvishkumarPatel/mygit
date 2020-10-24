/* object defination of:
    - commit
    - blob
        - hash_object
        - compress the new content
        -
    - tree
and helper classes and definations
*/




#include "object.h"
// #include <string>
// #include <iostream>
// using namespace std;

//test hash_object
int main(int argc, char* argv[]){
    const string content= argv[1];
    const string hash= hash_object(content);
    cout << hash << endl;
    return 0;
}


