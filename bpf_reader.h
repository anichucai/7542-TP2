#ifndef BPF_READER_H_
#define BPF_READER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>

class BpfReader{
 public:
        BpfReader(std::string &file_name);
        int getLine(std::string &instruction);
        ~BpfReader();

 private:
        bool emptyLine(std::string &line);
        std::ifstream in_file;
};

#endif  // BPF_READER_H_
