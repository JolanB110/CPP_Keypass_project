#ifndef USER_HPP
#define USER_HPP

#include <vector>
#include <string>
#include "Mdp.hpp"

//classe pour le 2FA
class TwoFactor {
private:
    std::string secret;
    bool enabled;

public:
    TwoFactor() : secret(""), enabled(false) {}

    void enable();
    void disable();
    bool isEnabled() const { return enabled; }
    std::string getSecret() const { return secret; }
    std::string generateCode();
    bool verifyCode(const std::string& userCode);
};

//classe pour le chiffrement des mots de passe
class Encryption {
public:
    static std::string encryptPassword(const std::string& password, int shift = 5);
    static std::string decryptPassword(const std::string& encrypted, int shift = 5);
};

class User {
private:
    std::string username;
    std::string masterPassword;
    std::vector<Mdp> mdp;
    TwoFactor twoFA;              

public:
    User(const std::string& username, const std::string& masterPassword);

    bool verifConnexion(const std::string& username,
                        const std::string& masterPassword);

    std::string getUsername() const {
        return username;
    }

    std::string getMasterPassword() const {
        return masterPassword;
    }

    std::vector<Mdp>& getMdp() {
        return mdp;
    }

    const std::vector<Mdp>& getMdp() const {
        return mdp;
    }

    bool changeMasterPassword(const std::string& oldPassword,
                              const std::string& newPassword) {
        if (oldPassword != masterPassword) {
            return false;  
        }
        if (newPassword.empty()) {
            return false;  
        }
        masterPassword = newPassword;
        return true;
    }

    //méthodes 2FA
    void enable2FA() { twoFA.enable(); }
    void disable2FA() { twoFA.disable(); }
    bool is2FAEnabled() const { return twoFA.isEnabled(); }
    std::string get2FASecret() const { return twoFA.getSecret(); }
    std::string get2FACode() { return twoFA.generateCode(); }
    bool verify2FA(const std::string& code) { return twoFA.verifyCode(code); }
};

#endif
