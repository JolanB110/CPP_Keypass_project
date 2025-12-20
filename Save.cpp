#include "Save.hpp"
#include "Label.hpp"
#include "User.hpp"
#include "Mdp.hpp"
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

void Save(const std::vector<User>& users, const std::vector<Label> tag) {
    std::ofstream file("users.dat");
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing.");
    }

    for (const auto& user : users) {
        file << user.getUsername() << "|" << Mdp::encryptedPassword(user.getMasterPassword()) << "|" 
             << user.getMdp().size() << "\n";
        
        //on sauvegarde les mots de passe de cet utilisateur
        for (const auto& mdp : user.getMdp()) {
            file << mdp.getName() << "|" << Mdp::encryptedPassword(mdp.getPassword()) << "|" 
                 << mdp.getLabel() << "\n";
        }
    }
    file << "---LABELS---\n";
    for (size_t i = 0; i < tag.size(); i++) {
        file << tag[i].getName() << "\n";
    }
    
    file.close();
}
std::vector<User> Import() {
    std::vector<User> users;
    std::ifstream file("users.dat");
    if (!file.is_open()) {
        std::cout << "Aucun fichier de sauvegarde trouver. Nouveau fichier creer au premier enregistrement.\n";
        return users;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line == "---LABELS---") continue;
        
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        
        if (pos1 != std::string::npos && pos2 != std::string::npos) {
            std::string username = line.substr(0, pos1);
            std::string password = Mdp::decryptedPassword(line.substr(pos1 + 1, pos2 - pos1 - 1));
            
            //extraction et validation de la partie numérique
            std::string nbMdpStr = line.substr(pos2 + 1);
            
            //supprimer les espaces blancs éventuels
            nbMdpStr.erase(0, nbMdpStr.find_first_not_of(" \t\n\r"));
            nbMdpStr.erase(nbMdpStr.find_last_not_of(" \t\n\r") + 1);
            
            // Vérifier que la chaîne n'est pas vide et contient uniquement des chiffres
            if (nbMdpStr.empty() || nbMdpStr.find_first_not_of("0123456789") != std::string::npos) {
                std::cerr << "Erreur: nombre de mots de passe invalide pour l'utilisateur " 
                          << username << ". Ligne ignoree.\n";
                continue;
            }
            
            int nbMdp = 0;
            try {
                nbMdp = std::stoi(nbMdpStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Erreur de conversion pour l'utilisateur " << username 
                          << ". Ligne ignoree.\n";
                continue;
            } catch (const std::out_of_range& e) {
                std::cerr << "Nombre trop grand pour l'utilisateur " << username 
                          << ". Ligne ignoree.\n";
                continue;
            }
            
            User user(username, password);
            
            //charger les mots de passe associés
            for (int i = 0; i < nbMdp; i++) {
                if (std::getline(file, line)) {
                    if (line == "---LABELS---") {
                        break;
                    }
                    
                    size_t p1 = line.find('|');
                    size_t p2 = line.find('|', p1 + 1);
                    
                    if (p1 != std::string::npos && p2 != std::string::npos) {
                        std::string appName = line.substr(0, p1);
                        std::string appPwd = Mdp::decryptedPassword(line.substr(p1 + 1, p2 - p1 - 1));
                        std::string label = line.substr(p2 + 1);
                        user.getMdp().push_back(Mdp(appName, appPwd, label));
                    }
                }
            }
            users.push_back(user);
        }
    }
    
    file.close();
    std::cout << "Donnees chargees depuis la sauvegarde\n";
    return users;
}



