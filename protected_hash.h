#ifndef PROTECTED_HASH_H_
#define PROTECTED_HASH_H_

#include <unordered_map>
#include <pthread.h>
#include <mutex>
#include <string>

class ProtectedHash{
 public:
        ProtectedHash();
        void getHash(std::unordered_map<std::string, int>* map);
        void addUnique(std::string key, int value);
        ~ProtectedHash();

 private:
        std::unordered_map<std::string, int> hash;
        std::mutex m_write;
};

#endif   // PROTECTED_HASH_H_
