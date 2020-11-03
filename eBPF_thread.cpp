#ifndef EBPF_THREAD_H_
#define EBPF_THREAD_H_

#include "base_thread.cpp"

#include "protected_vector.h"
#include "protected_hash.h"
#include "eBPF.h"

class EBpfThread : public Thread{
 private:
        ProtectedHash* p_res;
        ProtectedVector* p_fil;

 public:
        EBpfThread(ProtectedHash* result, ProtectedVector* files) {
            this->p_res = result;
            this->p_fil = files;
        }
        virtual void run() {
            EBPF ebpf;
            std::string file_name;
            int has_file = this->p_fil->getUnique(&file_name);
            if (has_file == -1) {
                return;
            }
            int res = ebpf.identifyCycle(file_name);
            this->p_res->addUnique(file_name, res);
        }
        ~EBpfThread() {}
};

#endif   // EBPF_THREAD_H_
