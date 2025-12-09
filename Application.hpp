#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>

class Application {

public:
    std::string name;      
    std::string type;

private:
    std::string mail;
    std::string path_to_user;
    int numero_carte;
    int CCV;
    std::string date_expiration;
};

#endif