#include <iostream>
using namespace std;
#include <fstream>

#include "bpf_instruction.h"


void linear_arg(){
    cout << "Test linear_arg" << endl;
    string s = "        ldh [12]";
    BpfInstruction inst(s);
    cout << "- instruction: " << s << endl;
    bool correct = true;
    correct &= (inst.typeInstruction() == 1);
    correct &= (inst.hasLabel() == false);
    correct &= (inst.cantArguments() == 1);
    string arg;
    inst.getArgument(arg,1);
    correct &= (arg == "[12]");
    cout << "CORRECT? " << correct << endl << endl;
}

void jump_1arg(){
    cout << "Test jump_1arg" << endl;
    string s = "        ja drop";
    BpfInstruction inst(s);
    cout << "- instruction: " << s << endl;
    bool correct = true;
    correct &= (inst.typeInstruction() == 2);
    correct &= (inst.hasLabel() == false);
    correct &= (inst.cantArguments() == 1);
    string arg;
    inst.getArgument(arg,1);
    correct &= (arg == "drop");
    cout << "CORRECT? " << correct << endl << endl;
}

void jump_2arg(){
    cout << "Test jump_2arg" << endl;
    string s = "        jne #0x806, drop";
    BpfInstruction inst(s);
    cout << "- instruction: " << s << endl;
    bool correct = true;
    correct &= (inst.typeInstruction() == 2);
    correct &= (inst.hasLabel() == false);
    correct &= (inst.cantArguments() == 2);
    string arg1, arg2;
    inst.getArgument(arg1,1);
    inst.getArgument(arg2,2);
    correct &= (arg1 == "#0x806");
    correct &= (arg2 == "drop");
    cout << "CORRECT? " << correct << endl << endl;
}

void jump_3arg(){
    cout << "Test jump_3arg" << endl;
    string s = "        jne #0x806, drop, 22";
    BpfInstruction inst(s);
    cout << "- instruction: " << s << endl;
    bool correct = true;
    correct &= (inst.typeInstruction() == 2);
    correct &= (inst.hasLabel() == false);
    correct &= (inst.cantArguments() == 3);
    string arg1, arg2, arg3;
    inst.getArgument(arg1,1);
    inst.getArgument(arg2,2);
    inst.getArgument(arg3,3);
    correct &= (arg1 == "#0x806");
    correct &= (arg2 == "drop");
    correct &= (arg3 == "22");
    cout << "CORRECT? " << correct << endl << endl;
}

void ret_arg(){
    cout << "Test ret_arg" << endl;
    string s = "        ret [12]";
    BpfInstruction inst(s);
    cout << "- instruction: " << s << endl;
    bool correct = true;
    correct &= (inst.typeInstruction() == 3);
    correct &= (inst.hasLabel() == false);
    correct &= (inst.cantArguments() == 1);
    string arg;
    inst.getArgument(arg,1);
    correct &= (arg == "[12]");
    cout << "CORRECT? " << correct << endl << endl;
}

void label_linear_arg(){
    cout << "Test label_linear_arg" << endl;
    string s = "drop:        ldh [12]";
    BpfInstruction inst(s);
    cout << "- instruction: " << s << endl;
    bool correct = true;
    correct &= (inst.typeInstruction() == 1);
    correct &= (inst.hasLabel() == true);
    correct &= (inst.cantArguments() == 1);
    string arg;
    inst.getArgument(arg,1);
    correct &= (arg == "[12]");
    cout << "ARGg: "<< arg << endl;
    cout << "CORRECT? " << correct << endl << endl;
}

void label_jump_1arg(){
    cout << "Test label_jump_1arg" << endl;
    string s = "drop:        ja drop";
    BpfInstruction inst(s);
    cout << "- instruction: " << s << endl;
    bool correct = true;
    correct &= (inst.typeInstruction() == 2);
    correct &= (inst.hasLabel() == true);
    correct &= (inst.cantArguments() == 1);
    string arg;
    inst.getArgument(arg,1);
    correct &= (arg == "drop");
    cout << "CORRECT? " << correct << endl << endl;
}

void label_jump_2arg(){
    cout << "Test label_jump_2arg" << endl;
    string s = "drop:        jne #0x806, drop";
    BpfInstruction inst(s);
    cout << "- instruction: " << s << endl;
    bool correct = true;
    correct &= (inst.typeInstruction() == 2);
    correct &= (inst.hasLabel() == true);
    correct &= (inst.cantArguments() == 2);
    string arg1, arg2;
    inst.getArgument(arg1,1);
    inst.getArgument(arg2,2);
    correct &= (arg1 == "#0x806");
    correct &= (arg2 == "drop");
    cout << "CORRECT? " << correct << endl << endl;
}

void label_jump_3arg(){
    cout << "Test label_jump_3arg" << endl;
    string s = "drop:        jne #0x806, drop, 22";
    BpfInstruction inst(s);
    cout << "- instruction: " << s << endl;
    bool correct = true;
    correct &= (inst.typeInstruction() == 2);
    correct &= (inst.hasLabel() == true);
    correct &= (inst.cantArguments() == 3);
    string arg1, arg2, arg3;
    inst.getArgument(arg1,1);
    inst.getArgument(arg2,2);
    inst.getArgument(arg3,3);
    correct &= (arg1 == "#0x806");
    correct &= (arg2 == "drop");
    correct &= (arg3 == "22");
    cout << "CORRECT? " << correct << endl << endl;
}

void label_ret_arg(){
    cout << "Test label_ret_arg" << endl;
    string s = "drop:        ret [12]";
    BpfInstruction inst(s);
    cout << "- instruction: " << s << endl;
    bool correct = true;
    correct &= (inst.typeInstruction() == 3);
    correct &= (inst.hasLabel() == true);
    correct &= (inst.cantArguments() == 1);
    string arg;
    inst.getArgument(arg,1);
    correct &= (arg == "[12]");
    cout << "CORRECT? " << correct << endl << endl;
}

void label(){
    cout << "Test label" << endl;
    string s = "drop:        ret [12]";
    BpfInstruction inst(s);
    string label;
    bool correct = true;
    inst.getLabel(label);
    correct &= (label == "drop");
    cout << "CORRECT? " << correct << endl << endl;
}



int main(int argc, char *argv[]){
    cout <<"\n______TESTING_______\n\n";
    linear_arg();
    jump_1arg();
    jump_2arg();
    jump_3arg();
    ret_arg();
    label_linear_arg();
    label_jump_1arg();
    label_jump_2arg();
    label_jump_3arg();
    label_ret_arg();
    label();
}