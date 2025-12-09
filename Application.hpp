#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>

class Application {

public:
    std::string name;      
    std::string type;
    
private:
    //Constructeurs
    Application(const std::string& name, const std::string& type);
    Application(const std::string& name, const std::string& type, std::string mail);
    Application(const std::string& name, const std::string& type, const std::string mail, const std::string path_to_user);
    Application(const std::string& name, const std::string& type, const std::string mail, const std::string path_to_user, int numero_carte, int CCV, const std::string date_expiration);

    std::string mail;
    std::string path_to_user;
    int numero_carte;
    int CCV;
    std::string date_expiration;
};

#endif