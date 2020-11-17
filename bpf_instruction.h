#ifndef BPF_INSTRUCTION_H_
#define BPF_INSTRUCTION_H_
#include <iostream>
#include <fstream>
#include <map>
#include <string>

class BpfInstruction{
 public:
        explicit BpfInstruction(const std::string &inst);
        bool hasLabel();
        int typeInstruction();
        void getLabel(std::string &label);
        void getArgument(std::string &arg, int i);
        int numArguments();
        ~BpfInstruction();

 private:
        std::string label;
        std::string op_code;
        std::string args;

        bool has_label;
        int num_arg = 0;

        void setLabel(const std::string &inst);
        void setOpCode(const std::string &inst);
        void setArgs(const std::string &inst);
        int getArgPos(const std::string &inst);
        void setCantArguments(const std::string &inst);
};

#endif  // BPF_INSTRUCTION_H_
