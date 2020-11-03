#include <iostream>
using namespace std;
#include <fstream>

#include "eBPF.h"

int main(int argc, char *argv[]){
    
    string line;
    string file_name = argv[1];

    EBPF eBPF;
    unordered_map<string, int> res;
    
    eBPF.applyEBPF(file_name);
    eBPF.getResults(&res);
    cout << file_name << ": " << res[file_name] << endl;
    
    return 0;
}
