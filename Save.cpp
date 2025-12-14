#include "Save.hpp"
#include "Label.hpp"
#include "User.hpp"
#include <fstream>
#include <vector>

void Save(const std::vector<Data>& Data, const std::vector<Label> tag) {
    std::ofstream write_output("Save.dat");

    for (size_t i = 0; i < Data.size(); i++) {
        write_output << Data[i].name << " " << Data[i].password << " " << Data[i].label << "\n";
    }

    for (size_t i = 0; i < tag.size(); i++) {
        write_output << tag[i].getName() << "\n";
    }

    write_output.close();
}

/*

void Save(const std::vector<User>& users) {
    std::ofstream file("users.dat");
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier de sauvegarde\n";
        return;
    }
    
    for (const auto& user : users) {
        // Format : username|masterPassword|nbMdp
        file << user.getUsername() << "|" << user.getMasterPassword() << "|" 
             << user.getMdp().size() << "\n";
        
        for (const auto& mdp : user.getMdp()) {
            file << mdp.getName() << "|" << mdp.getPassword() << "|" 
                 << mdp.getLabel() << "\n";
        }
    }
    file.close();
    std::cout << "Données sauvegardées avec succès\n";
}

std::vector<User> Import() {
    std::vector<User> users;
    std::ifstream file("users.dat");
    
    if (!file.is_open()) {
        std::cout << "Aucun fichier de sauvegarde trouvé. Nouveau fichier créé au premier enregistrement.\n";
        return users;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        // Parser la ligne utilisateur
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        
        if (pos1 != std::string::npos && pos2 != std::string::npos) {
            std::string username = line.substr(0, pos1);
            std::string password = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int nbMdp = std::stoi(line.substr(pos2 + 1));
            
            User user(username, password);
            
            // Charger les mots de passe associés
            for (int i = 0; i < nbMdp; i++) {
                if (std::getline(file, line)) {
                    size_t p1 = line.find('|');
                    size_t p2 = line.find('|', p1 + 1);
                    
                    if (p1 != std::string::npos && p2 != std::string::npos) {
                        std::string appName = line.substr(0, p1);
                        std::string appPwd = line.substr(p1 + 1, p2 - p1 - 1);
                        std::string label = line.substr(p2 + 1);
                        
                        user.getMdp().push_back(Mdp(appName, appPwd, label));
                    }
                }
            }
            
            users.push_back(user);
        }
    }
    file.close();
    std::cout << "Données chargées depuis la sauvegarde\n";
    return users;
}
    */