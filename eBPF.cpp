#include "eBPF.h"
#include "constants.h"

#include <algorithm>
#include <thread>
#include <utility>
#include <string>
#include <unordered_map>

EBPF::EBPF(const std::string &file_name): r(file_name) {
    setLabel();
    setG();
}

void EBPF::setLabel() {
    std::string instruction;
    int instruction_id = 0;
    int _eof = r.getLine(instruction);

    while (_eof != -1) {
        std::string label;
        BpfInstruction bpf_inst(instruction);
        if (bpf_inst.hasLabel() == true) {
            bpf_inst.getLabel(label);
            l.insert(std::pair<std::string, int> (label, instruction_id));
        }
        _eof = r.getLine(instruction);
        instruction_id++;
    }
}

void EBPF::setG() {
    std::string instruction;
    int instruction_id = 0;
    int _eof = this->r.getLine(instruction);
    while (_eof != -1) {
        BpfInstruction bpf_inst(instruction);
        if (bpf_inst.typeInstruction() == LINEAR) {
            this->g.addChild(instruction_id, instruction_id+1);
        } else if (bpf_inst.typeInstruction() == JUMP) {
            int cant_args = bpf_inst.numArguments();
            std::string arg1, arg2;
            if (cant_args == 1) {
                bpf_inst.getArgument(arg1, 1);
                this->g.addChild(instruction_id, this->l[arg1]);
            } else if (cant_args == 2) {
                bpf_inst.getArgument(arg2, 2);
                this->g.addChild(instruction_id, this->l[arg2]);
                this->g.addChild(instruction_id, instruction_id+1);
            } else if (cant_args == 3) {
                bpf_inst.getArgument(arg1, 2);
                bpf_inst.getArgument(arg2, 3);
                this->g.addChild(instruction_id, this->l[arg1]);
                this->g.addChild(instruction_id, this->l[arg2]);
            }
        } else if (bpf_inst.typeInstruction() != RET) {
            this->g.addChild(instruction_id, instruction_id+1);
        }
        _eof = this->r.getLine(instruction);
        instruction_id++;
    }
}

void EBPF::getResult(std::string &res) {
    if (this->g.isCyclic() == CYCLIC) {
        res = "FAIL: cycle detected";
    } else if (this->g.isFullyVisited() != FULLY_VISITED) {
        res = "FAIL: unused instructions detected";
    } else {
        res = "GOOD";
    }
}

EBPF::~EBPF() {}
