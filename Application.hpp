#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>
#include <iostream>

/* Ancienne version de la classe Application, a garder pour référence
class Application {

public:
    std::string name;      
    std::string type;
    
protected:
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

*/

class Application { 
protected:
    std::string name;
    std::string type;
    std::string mail;
    std::string path_to_user;

public://constructeur d'application
    Application(const std::string& name, const std::string& type);
    virtual ~Application() = default;//méthode virtuelle 

    virtual void displayInfo() const {
        std::cout << "Application: " << name << " (" << type << ")" << '\n';
    }
    
    virtual bool validate() const = 0;
    
    std::string getName() const { return name; }
};

class EmailApplication : public Application {
private:
    std::string mailAddress;
    
public: //constructeur d'email avec sa méthode virtuelle
    EmailApplication(const std::string& name, const std::string& type, 
                     const std::string& mail);
    
    void displayInfo() const override {
        Application::displayInfo();
        std::cout << "Email: " << mailAddress << '\n';
    }
    
    bool validate() const override {  //doit contenir un '@' pour que la mail soit valide
        return !mailAddress.empty() && mailAddress.find('@') != std::string::npos;
    }
};

class BankApplication : public Application {
private:
    int cardNumber;
    int cvv;
    std::string expirationDate;
    
public: //constructeur de bankApplication avec sa méthode virtuelle
    BankApplication(const std::string& name, const std::string& type,
                    int cardNum, int cvv, const std::string& expDate);
    
    void displayInfo() const override {
        Application::displayInfo();
        std::cout << "Carte: ****" << (cardNumber % 10000) << " (CVV: ***)" << '\n';  //affichage a revoir
    }
    
    bool validate() const override { //doit contenir le num de carte, le cvv et la date d'expiration pour être valide
        return cardNumber > 0 && cvv > 0 && !expirationDate.empty();
    }
};

#endif