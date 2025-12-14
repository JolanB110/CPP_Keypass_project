#ifndef USER_HPP
#define USER_HPP

#include <vector>
#include <string>
#include "Mdp.hpp"

class User {
private:
    std::string username;
    std::string masterPassword;
    std::vector<Mdp> mdp;

public:
    User(const std::string& username, const std::string& masterPassword); //constructeur 1 test
    
    bool verifConnexion(const std::string& username, const std::string& masterPassword);

    std::string getUsername() const {
        return username; 
    }

    std::vector<Mdp>& getMdp() {
        return mdp; 
    }
    bool changeMasterPassword(const std::string& oldPassword, 
                         const std::string& newPassword) {
    if (oldPassword != masterPassword) {
        return false;  // L'ancien mot de passe est incorrect
    }
    if (newPassword.empty()) {
        return false;  // Le nouveau mot de passe ne peut pas être vide
    }
    masterPassword = newPassword;
    return true;
}
};

#endif