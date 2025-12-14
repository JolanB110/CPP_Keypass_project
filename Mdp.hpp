#ifndef MDP_HPP
#define MDP_HPP

#include <string>
#include <random>
#include <algorithm>

class Mdp {

public:
    std::string name;      
    std::string Password;
    std::string label;

    Mdp(const std::string& name, const std::string& Password)
        : name(name), Password(Password) {}
    
    Mdp(const std::string& name, const std::string& Password, const std::string& label)
        : name(name), Password(Password), label(label) {}

    std::string getName() const { 
        return name; 
    }

    std::string getPassword() const { 
        return Password; 
    }

    std::string getLabel() const {
        return label;
    }

    static std::string mdpgenerator(int length = 16, bool includeSpecial = true) {
        std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
        std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string numbers = "0123456789";
        std::string special = "!@#$%^&*-_+=";
    
        std::string charset = lowercase + uppercase + numbers;
        if (includeSpecial) {
            charset += special;
            }
    
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, charset.length() - 1);
    
        std::string password;
        for (int i = 0; i < length; i++) {
            password += charset[dis(gen)];
        }
        return password;
}
};

#endif