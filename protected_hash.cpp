#include "protected_hash.h"
#include <utility>
#include <string>

ProtectedHash::ProtectedHash() {}

void ProtectedHash:: getHash(std::unordered_map<std::string, int>* map) {
    *map = this->hash;
}

void ProtectedHash:: addUnique(std::string key, int value) {
    m_write.lock();
    this->hash.insert(std::pair <std::string, int>(key, value));
    m_write.unlock();
}

ProtectedHash::~ProtectedHash() {}
