#include "eBPF_checker.h"
#include <string>
EBPFChecker::EBPFChecker(int argc, char* argv[]) {
    for (int i = 2; i < argc; i++) {
        this->files.push_back(argv[i]);
    }

    this->num_theads = atoi(argv[1]);
    this->num_files = argc - 2;
}

void EBPFChecker::run() {
    Repository repo(this->files);
    this->getResults(repo);
    this->printResults(repo);
}

void EBPFChecker::getResults(Repository &repo) {
    int j = 0;
    while (j < this->num_files) {
        std::vector<Thread*> threads;
        int max;
        if (this->num_files - j > this->num_theads) {
            max = this->num_theads;
        } else {
            max = this->num_files - j;
        }
        for (int i = 0; i < max; ++i) {
            threads.push_back(new EBpfThread(repo));
            threads[i]->start();
        }
        for (int i = 0; i < max; ++i) {
            threads[i]->join();
            delete threads[i];
        }
        j += max;
    }
}

void EBPFChecker::printResults(Repository &repo) {
    std::string key, val;
    while (repo.getResult(key, val) != -1) {
        std::cout << key << " " << val << std::endl;
    }
}

EBPFChecker::~EBPFChecker() {
}
