#include <iostream>
using namespace std;
#include <fstream>

#include "eBPF.h"

int main(int argc, char *argv[]){
    
    string line;
    string file_name = argv[1];

    EBPF eBPF(file_name);
    
    string res;
    eBPF.getResult(res);
    cout << file_name << ": " << res << endl;
    
    return 0;
}
