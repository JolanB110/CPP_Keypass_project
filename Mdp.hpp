#ifndef MDP_HPP
#define MDP_HPP

#include <string>

class Mdp {

public:
    std::string name;      
    std::string Password;
    std::string label;

    Mdp(const std::string& name, const std::string& Password)
        : name(name), Password(Password) {}
    
    Mdp(const std::string& name, const std::string& Password, const std::string& label)
        : name(name), Password(Password), label(label) {}

    std::string getName() const { 
        return name; 
    }

    std::string getPassword() const { 
        return Password; 
    }

    std::string getLabel() const {
        return label;
    }

    std::string mdpgenerator(){
        std::string list="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKMNLOPQRSTUVWXYZ0123456789-_|[]{}()#&,;:!/.%$*¨^~?+=@èéàçù";
        std::string mdp="";
        
        for(int i=0;i<16;i++){ //on veut 16 caractères dans notre mot de passe

            int random = rand() % list.length(); //on génère un nombre aléatoire
            mdp += list[random];                 //on l'ajouter au mot de passe

        }
        return mdp;
    }

};

#endif