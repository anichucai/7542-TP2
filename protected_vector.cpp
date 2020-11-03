#include "protected_vector.h"

ProtectedVector::ProtectedVector() {}

void ProtectedVector::addVector(std::vector<std::string> vect) {
    this->v = vect;
}

int ProtectedVector::getUnique(std::string* val) {
    this->m_read.lock();
    if (this->v.empty()) {
        return -1;
    }
    size_t i = this->v.size();
    *val = this->v[i-1];
    this->v.pop_back();
    this->m_read.unlock();

    return 0;
}

ProtectedVector::~ProtectedVector() {}
