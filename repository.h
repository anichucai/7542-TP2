#ifndef REPOSITORY_H_
#define REPOSITORY_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>

class Repository {
 public:
        explicit Repository(const std::vector<std::string> &keys);
        int getKey(std::string &key);
        void addResult(const std::string &key, const std::string &res);
        int getResult(std::string &key_res, std::string &res);
        ~Repository();

 private:
        std::unordered_map<std::string, std::string> results;
        std::vector<std::string> keys;
        std::vector<std::string> keys_res;

        std::mutex m_read;
        std::mutex m_write;
};

#endif  // REPOSITORY_H_
