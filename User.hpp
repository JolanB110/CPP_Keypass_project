#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
private:
    std::string username;
    std::string masterPassword;

public:
    User(const std::string& username, const std::string& masterPassword); //constructeur 1 test
    
    bool verifConnexion(const std::string& username, const std::string& masterPassword);

    std::string getUsername() const { return username; }

};

#endif