#ifndef MDP_HPP
#define MDP_HPP

#include <string>

class Mdp {

public:
    std::string name;      
    std::string Password;

    Mdp(const std::string& name, const std::string& Password)
        : name(name), Password(Password) {}


    std::string getName() const { 
        return name; 
    }

    std::string getPassword() const { 
        return Password; 
    }

};

#endif