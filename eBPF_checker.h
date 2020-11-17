#ifndef EBPF_CHECKER_H_
#define EBPF_CHECKER_H_

#include <string>
#include <vector>

#include "base_thread.cpp"
#include "eBPF_thread.cpp"
#include "eBPF.h"
#include "repository.h"

class EBPFChecker {
 public:
    EBPFChecker(int argc, char* argv[]);
    void run();
    ~EBPFChecker();
 private:
    std::vector<std::string> files;
    int num_theads;
    int num_files;

    void getResults(Repository &repo);
    void printResults(Repository &repo);
};

#endif    // EBPF_CHECKER_H_
