#include "Mdp.hpp"

// Constructeurs
Mdp::Mdp(const std::string& name, const std::string& Password)
    : name(name), Password(Password) {}

Mdp::Mdp(const std::string& name, const std::string& Password, const std::string& label)
    : name(name), Password(Password), label(label) {}

// Getters
std::string Mdp::getName() const { return name; }
std::string Mdp::getPassword() const { return Password; }
std::string Mdp::getLabel() const { return label; }

// Générateur de mot de passe
std::string Mdp::mdpgenerator(int length, bool includeSpecial) {
    std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string numbers = "0123456789";
    std::string special = "!@#$%^&*-_+=";

    std::string charset = lowercase + uppercase + numbers;
    if (includeSpecial) charset += special;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, charset.length() - 1);

    std::string password;
    for (int i = 0; i < length; i++) {
        password += charset[dis(gen)];
    }
    return password;
}
