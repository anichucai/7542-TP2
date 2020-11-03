#include "eBPF.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "protected_vector.h"
#include "protected_hash.h"
#include "base_thread.cpp"
#include "eBPF_thread.cpp"
#include "eBPF.h"

enum TypeInstructions { NOT_CYCLIC = 0, CYCLIC = 1, UNSTACKED = 2};

int main(int argc, char *argv[]) {
    // Get files:
    std::vector<std::string> files;
    for (int i = 2; i < argc; i++) {
        files.push_back(argv[i]);
    }

    // EBPF with threads:
    int cant_theads = atoi(argv[1]);
    int cant_f = argc-2;

    ProtectedHash p_res;
    ProtectedVector p_fil;
    p_fil.addVector(files);

    int j = 0;

    while (j < cant_f) {
        std::vector<Thread*> threads;
        int max = (cant_f - j > cant_theads) ? cant_theads : cant_f - j;
        for (int i = 0; i < max; ++i) {
            threads.push_back(new EBpfThread(&p_res, &p_fil));
            threads[i]->start();
        }
        for (int i = 0; i < max; ++i) {
            threads[i]->join();
            delete threads[i];
        }
        j += max;
    }

    // Print Results:
    std::unordered_map<std::string, int> hash;
    p_res.getHash(&hash);
    std::sort(files.begin(), files.end());
    std::vector<std::string>::iterator it = files.begin();
    for (; it != files.end(); ++it) {
        std::cout << *it << " ";
        if (hash[*it] == CYCLIC) {
            std::cout << "FAIL: cycle detected";
        } else if (hash[*it] == UNSTACKED) {
            std::cout << "FAIL: unused instructions detected";
        } else if (hash[*it] == NOT_CYCLIC) {
            std::cout << "GOOD";
        }
        std::cout << std::endl;
    }

    return 0;
}
