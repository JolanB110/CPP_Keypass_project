#ifndef SAVE_HPP
#define SAVE_HPP

#include <string>
#include <vector>

struct Data {
    std::string name;
    std::string password;
    std::string label;
};

class User;
class Label;

void Save(const std::vector<User>& users, const std::vector<Label> tag);
std::vector<User> Import();


#endif
