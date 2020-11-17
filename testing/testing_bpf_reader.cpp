#include <iostream>
using namespace std;
#include <fstream>

#include "bpf_reader.h"


int main(int argc, char *argv[]){
    
    string line;
    string file_name = argv[1];
    BpfReader r(file_name);
    int _eof = r.getLine(line);
    int id = 0;
    while(_eof!=-1){
        cout<< "id" << id << ": " << line << endl;
        _eof = r.getLine(line);
        id++;
    }
    return 0;
}
