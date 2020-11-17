#ifndef EBPF_THREAD_H_
#define EBPF_THREAD_H_

#include "base_thread.cpp"
#include "eBPF.h"
#include "repository.h"
class EBpfThread : public Thread{
 private:
        Repository* repo;

 public:
        explicit EBpfThread(Repository &repo) {
            this->repo = &repo;
        }
        void run() override {
            std::string file_name;
            int has_file = this->repo->getKey(file_name);
            if (has_file == -1) {
                return;
            }
            EBPF ebpf(file_name);
            std::string res;
            ebpf.getResult(res);
            this->repo->addResult(file_name, res);
        }
        ~EBpfThread() {}
};

#endif   // EBPF_THREAD_H_
