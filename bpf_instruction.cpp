#include "bpf_instruction.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <set>
#define MAX_LEN 4

enum TypeInstructions { LINEAR = 1, JUMP = 2, RET = 3};

// PRIVATE METHODS

void BpfInstruction::setLabel(string inst) {
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

void BpfInstruction::setOpCode(string inst) {
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

int BpfInstruction::getArgPos(string inst) {
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

void BpfInstruction::setCantArguments(string inst) {
    this->cant_arg = std::count(inst.begin(), inst.end(), ',');
    this->cant_arg++;
}

void BpfInstruction::setArgs(string inst) {
    size_t start = this->getArgPos(inst);
    this->args = inst.substr(start);
    string::iterator it;
    it = this->args.end();
    this->args.erase(remove(this->args.begin(), it, ' '), it);
}

// PUBLIC METHODS

BpfInstruction::BpfInstruction(string instruction) {
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

void BpfInstruction::getArgument(string* arg, int i) {
    int j = 0;
    stringstream ss(this->args);

    for (; j < i; j++) {
        getline(ss, *arg, ',');
    }
}

void BpfInstruction::getLabel(string* label) {
    *label = this->label;
}


int BpfInstruction::cantArguments() {
    return this->cant_arg;
}

BpfInstruction::~BpfInstruction() {}
