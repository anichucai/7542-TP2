#include "eBPF_checker.h"

int main(int argc, char *argv[]) {
    EBPFChecker checker(argc, argv);
    checker.run();

    return 0;
}
