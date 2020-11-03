#ifndef PROTECTED_VECTOR_H_
#define PROTECTED_VECTOR_H_

#include <vector>
#include <pthread.h>
#include <mutex>
#include <string>

class ProtectedVector {
 public:
        ProtectedVector();
        void addVector(std::vector<std::string> vect);
        int getUnique(std::string* value);
        ~ProtectedVector();

 private:
        std::vector<std::string> v;
        std::mutex m_read;
};

#endif  // PROTECTED_VECTOR_H_
