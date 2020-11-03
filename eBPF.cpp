#include "eBPF.h"
#include <algorithm>
#include <thread>
#include <utility>
#include <string>
#include <unordered_map>

// muy feo pero cpplint se quejaba:
#define HASH std::unordered_map<std::string, int>

#define START_ID 0
enum TypeInstructions { LINEAR = 1, JUMP = 2, RET = 3};

EBPF::EBPF() {}

void EBPF::setLabel(BpfReader* r, std::unordered_map<std::string, int>* l) {
    std::string instruction;
    int instruction_id = START_ID;
    int _eof = r->getLine(&instruction);

    while (_eof != -1) {
        std::string label;
        BpfInstruction bpf_inst(instruction);
        if (bpf_inst.hasLabel() == true) {
            bpf_inst.getLabel(&label);
            l->insert(std::pair<std::string, int> (label, instruction_id));
        }
        _eof = r->getLine(&instruction);
        instruction_id++;
    }
}

void EBPF::setG(BpfReader* r, HASH* l, DGraph* g) {
    std::string instruction;
    int instruction_id = START_ID;
    int _eof = r->getLine(&instruction);
    while (_eof != -1) {
        BpfInstruction bpf_inst(instruction);
        if (bpf_inst.typeInstruction() == LINEAR) {
            g->addChild(instruction_id, instruction_id+1);
        } else if (bpf_inst.typeInstruction() == JUMP) {
            int cant_args = bpf_inst.cantArguments();
            std::string arg1, arg2;
            if (cant_args == 1) {
                bpf_inst.getArgument(&arg1, 1);
                g->addChild(instruction_id, (*l)[arg1]);
            } else if (cant_args == 2) {
                bpf_inst.getArgument(&arg2, 2);
                g->addChild(instruction_id, (*l)[arg2]);
                g->addChild(instruction_id, instruction_id+1);
            } else if (cant_args == 3) {
                bpf_inst.getArgument(&arg1, 2);
                bpf_inst.getArgument(&arg2, 3);
                g->addChild(instruction_id, (*l)[arg1]);
                g->addChild(instruction_id, (*l)[arg2]);
            }
        } else if (bpf_inst.typeInstruction() != RET) {
            g->addChild(instruction_id, instruction_id+1);
        }
        _eof = r->getLine(&instruction);
        instruction_id++;
    }
}

int EBPF::identifyCycle(std::string file_name) {
    BpfReader reader(file_name);
    std::unordered_map<std::string, int> labels;
    DGraph g;

    this->setLabel(&reader, &labels);
    this->setG(&reader, &labels, &g);
    return g.isCyclicDfs(START_ID);
}

EBPF::~EBPF() {}
