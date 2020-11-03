#ifndef BPF_INSTRUCTION_H_
#define BPF_INSTRUCTION_H_
#include <iostream>
#include <fstream>
#include <map>
#include <string>

class BpfInstruction{
 public:
        BpfInstruction(std::string inst);
        bool hasLabel();
        int typeInstruction();
        void getLabel(std::string* label);
        void getArgument(std::string* arg, int i);
        int cantArguments();
        ~BpfInstruction();

 private:
        std::string label;
        std::string op_code;
        std::string args;

        bool has_label;
        int cant_arg = 0;

        void setLabel(std::string inst);
        void setOpCode(std::string inst);
        void setArgs(std::string inst);
        int getArgPos(std::string inst);
        void setCantArguments(std::string inst);
};

#endif  // BPF_INSTRUCTION_H_
