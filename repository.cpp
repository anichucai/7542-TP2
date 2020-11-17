
#include "repository.h"
#include <algorithm>
#include <iostream>
#include <functional>
#include <utility>

Repository::Repository(const std::vector<std::string> &keys) {
    this->keys = keys;
    this->keys_res = keys;
}

int Repository::getKey(std::string &key) {
    this->m_read.lock();
    if (this->keys.empty()) {
        this->m_read.unlock();
        return -1;
    }
    size_t i = this->keys.size();
    key = this->keys[i-1];
    this->keys.pop_back();
    this->m_read.unlock();

    return 0;
}

void Repository::addResult(const std::string &key, const std::string &res) {
    m_write.lock();
    this->results.insert(std::pair <std::string, std::string>(key, res));
    m_write.unlock();
}

int Repository::getResult(std::string &key_res, std::string &res) {
    size_t i = this->keys_res.size();
    if (i == 0) {
        return -1;
    }
    std::sort(keys_res.begin(), keys_res.end(), std::greater<std::string>());
    std::string key = this->keys_res[i-1];
    this->keys_res.pop_back();
    res = results[key];
    key_res = key;
    return 0;
}

Repository::~Repository() {
}
