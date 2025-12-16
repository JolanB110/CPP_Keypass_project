#ifndef MDP_HPP
#define MDP_HPP

#include <string>
#include <random>

class Mdp {
public:
    std::string name;
    std::string Password;
    std::string label;

    Mdp(const std::string& name, const std::string& Password);
    Mdp(const std::string& name, const std::string& Password, const std::string& label);

    std::string getName() const;
    std::string getPassword() const;
    std::string getLabel() const;

    static std::string mdpgenerator(int length = 16, bool includeSpecial = true);
};

#endif
