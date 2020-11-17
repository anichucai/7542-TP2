#ifndef EBPF_H_
#define EBPF_H_

#include "bpf_instruction.h"
#include "bpf_reader.h"
#include "dgraph.h"
#include "repository.h"

#include <string>
#include <unordered_map>

class EBPF {
 public:
        explicit EBPF(const std::string &file_name);
        int isCyclic();
        int isFullyVisited();
        void getResult(std::string &res);
        ~EBPF();

 private:
       BpfReader r;
       std::unordered_map<std::string, int> l;
       DGraph g;

       void setG();
       void setLabel();
};

#endif   // EBPF_H_
