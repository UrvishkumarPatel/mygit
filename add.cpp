/*
comment - to compile use :  g++ add.cpp -lz
*/
#include "object.h"


int main(int argc, char* argv[]){
    string file_name=argv[1];
    cout<<file_name<<endl;
    add(file_name);
    return 0;
}
