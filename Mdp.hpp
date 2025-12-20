#ifndef MDP_HPP
#define MDP_HPP

#include <string>
#include <random>

class Mdp {
public:
    std::string name; //l'app est associé à un nom
    std::string Password; //elle a un mdp
    std::string label; //et un label 

    Mdp(const std::string& name, const std::string& Password);  //constructeur
    Mdp(const std::string& name, const std::string& Password, const std::string& label);

    std::string getName() const;
    std::string getPassword() const;
    std::string getLabel() const;

    std::string setLabel(const std::string& newLabel);

    static std::string mdpgenerator(int length = 16, bool includeSpecial = true);

    //méthodes statiques pour chiffrer et déchiffrer le mot de passe
    static std::string encryptedPassword(const std::string& password, int shift = 5);
    static std::string decryptedPassword(const std::string& encrypted, int shift = 5);
};

#endif
