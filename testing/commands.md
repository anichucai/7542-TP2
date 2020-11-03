# Commands

cd Documents/7542-TP2

## basic main

g++ -Wall main.cpp -o tp1
./tp1

## testing_bpf_instruction

g++ -Wall testing_bpf_instruction.cpp bpf_instruction.cpp bpf_instruction.h -o main1
valgrind ./main1

## testing_bpf_reader

g++ -Wall testing_bpf_reader.cpp bpf_reader.cpp bpf_reader.h -o main2
valgrind ./main2 casos/arp1.bpf
valgrind ./main2 casos/all_addr_modes.bpf

## testing_dgraph

g++ -Wall testing_dgraph.cpp dgraph.cpp dgraph.h -o main3
valgrind ./main3

## testing_eBPF

g++ -Wall testing_eBPF.cpp bpf_instruction.cpp bpf_instruction.h bpf_reader.cpp bpf_reader.h eBPF.cpp eBPF.h dgraph.cpp dgraph.h -o main4
valgrind ./main4 casos/arp1.bpf
valgrind ./main4 casos/all_addr_modes.bpf
valgrind ./main4 casos/all_jmps.bpf

## main

g++ -std=c++11 -pthread -Wall bpf_instruction.cpp bpf_instruction.h bpf_reader.cpp bpf_reader.h eBPF.cpp eBPF.h dgraph.cpp dgraph.h eBPF_main.cpp "protected_hash.h" "protected_hash.cpp" "protected_vector.h" "protected_vector.cpp" base_thread.cpp eBPF_thread.cpp -o main

./main 5 casos/arp.bpf casos/all_addr_modes.bpf casos/not_exec_inst2.bpf casos/not_exec_inst.bpf casos/arp1.bpf
