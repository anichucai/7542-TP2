#ifndef EBPF_H_
#define EBPF_H_

#include "bpf_instruction.h"
#include "bpf_reader.h"
#include "dgraph.h"
#include "protected_vector.h"
#include "protected_hash.h"

#include <string>
#include <unordered_map>

class EBPF {
 public:
        EBPF();
        int identifyCycle(std::string file_name);
        ~EBPF();

 private:
        void setG(BpfReader* r, std::unordered_map<std::string, int>* l, DGraph* g);
        void setLabel(BpfReader* r, std::unordered_map<std::string, int>* l);
};

#endif   // EBPF_H_
