#include "bpf_instruction.h"
#include "constants.h"

#include <algorithm>
#include <string>
#include <sstream>
#include <set>
#define MAX_LEN 4

// PRIVATE METHODS

void BpfInstruction::setLabel(std::string &inst) {
    size_t end = inst.find(':');
    size_t start = 0;

    if (end == std::string::npos) {
        this->has_label = false;
        return;
    }
    this->has_label = true;
    while (inst[start] == ' ') {
        start++;
    }

    this->label = inst.substr(start, end - start);
}

void BpfInstruction::setOpCode(std::string &inst) {
    int j = 0;
    size_t i = inst.find(":")+1;
    if (i == std::string::npos) {
        i = 0;
    }

    while (inst[i] == ' ') {
        i++;
    }
    while (inst[i] != ' ') {
        op_code[j] = inst[i];
        i++;
        j++;
    }
    this->op_code[j] = '\0';
}

int BpfInstruction::getArgPos(std::string &inst) {
    size_t i = 0;
    if (this->has_label) {
        i += inst.find(":")+1;
    }

    while (inst[i] == ' ') {
        i++;
    }
    while (inst[i] != ' ') {
        i++;
    }
    while (inst[i] == ' ') {
        i++;
    }

    return i;
}

void BpfInstruction::setCantArguments(std::string &inst) {
    this->num_arg = std::count(inst.begin(), inst.end(), ',');
    this->num_arg++;
}

void BpfInstruction::setArgs(std::string &inst) {
    size_t start = this->getArgPos(inst);
    this->args = inst.substr(start);
    std::string::iterator it;
    it = this->args.end();
    this->args.erase(remove(this->args.begin(), it, ' '), it);
}

// PUBLIC METHODS

BpfInstruction::BpfInstruction(std::string &instruction) {
    this->setOpCode(instruction);
    this->setLabel(instruction);
    this->setArgs(instruction);
    this->setCantArguments(instruction);
}

bool BpfInstruction::hasLabel() {
    return this->has_label;
}

int BpfInstruction::typeInstruction() {
    if (this->op_code[0] == 'l') {
        return LINEAR;
    } else if (this->op_code[0] == 'j') {
        return JUMP;
    } else if (this->op_code[0] == 'r') {
        return RET;
    } else {
        return -1;
    }
}

void BpfInstruction::getArgument(std::string &arg, int i) {
    int j = 0;
    std::stringstream ss(this->args);

    for (; j < i; j++) {
        getline(ss, arg, ',');
    }
}

void BpfInstruction::getLabel(std::string &label) {
    label = this->label;
}


int BpfInstruction::numArguments() {
    return this->num_arg;
}

BpfInstruction::~BpfInstruction() {}
