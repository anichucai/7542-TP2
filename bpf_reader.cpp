#include "bpf_reader.h"
#include <algorithm>
#include <string>
#include <sstream>

enum TypeInstructions { LINEAR = 1, JUMP = 2, RET = 3};

BpfReader::BpfReader(std::string file_name) {
    this->in_file.open(file_name);
}

bool BpfReader::emptyLine(std::string line) {
    int i = 0;
    while (line[i] == ' ') {
        i++;
    }
    return (line[i] == '\n' || line[i] == '\0');
}

int BpfReader::getLine(std::string* instruction) {
    if (!this->in_file) {
        this->in_file.clear();
        this->in_file.seekg(0);
        return -1;
    }

    getline(this->in_file, *instruction);
    while (emptyLine(*instruction)) {
        if (!this->in_file) {
            this->in_file.clear();
            this->in_file.seekg(0);
            return -1;
        }
        getline(this->in_file, *instruction);
    }
    return 0;
}

BpfReader::~BpfReader() {
    if (this->in_file) {
        this->in_file.close();
    }
}
