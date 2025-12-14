#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>

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

/*class Application {
protected:
    std::string name;
    std::string type;
    std::string mail;
    std::string path_to_user;

public:
    Application(const std::string& name, const std::string& type);
    virtual ~Application() = default;  //  Destructeur virtuel
    
    // Méthode virtuelle : afficher les informations
    virtual void displayInfo() const {
        std::cout << "Application: " << name << " (" << type << ")" << '\n';
    }
    
    // Méthode virtuelle : valider les données
    virtual bool validate() const = 0;  // Méthode pure virtuelle
    
    std::string getName() const { return name; }
};

// Classe dérivée pour les applications avec email
class EmailApplication : public Application {
private:
    std::string mailAddress;
    
public:
    EmailApplication(const std::string& name, const std::string& type, 
                     const std::string& mail);
    
    void displayInfo() const override {
        Application::displayInfo();
        std::cout << "Email: " << mailAddress << '\n';
    }
    
    bool validate() const override {
        return !mailAddress.empty() && mailAddress.find('@') != std::string::npos;
    }
};

// Classe dérivée pour les applications bancaires
class BankApplication : public Application {
private:
    int cardNumber;
    int cvv;
    std::string expirationDate;
    
public:
    BankApplication(const std::string& name, const std::string& type,
                    int cardNum, int cvv, const std::string& expDate);
    
    void displayInfo() const override {
        Application::displayInfo();
        std::cout << "Carte: ****" << (cardNumber % 10000) << " (CVV: ***)" << '\n';
    }
    
    bool validate() const override {
        return cardNumber > 0 && cvv > 0 && !expirationDate.empty();
    }
};
*/
#endif