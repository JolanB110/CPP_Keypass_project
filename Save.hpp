#ifndef SAVE_HPP
#define SAVE_HPP

#include <string>
#include <vector>

struct Data {
    std::string name;
    std::string password;
    std::string label;
};

void Save(const std::vector<Data>& users);

std::vector<Data> Import();

#endif
