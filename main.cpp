#include "User.hpp"
#include "Save.hpp"
#include "Mdp.hpp"
#include "Label.hpp"
#include "Application.hpp"
#include "PasswordTester.hpp"
#include "search_label.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <memory>


int main(){
    User* ActualUser = nullptr;
    int User_used;
    std::vector<User> users;
    std::string nom, mdp, etiquette;
    std::vector<Label> tag;
    users = Import();

    bool connexion_successful = false;
    std::string rep_init = "-1";
    std::string rep_home = "-1";
    std::string rep_mdp = "-1";
    std::string rep_search = "-1";

    while (rep_init != "0"){

        std::cout << "\n--- Menu Principal ---" << '\n';
        std::cout << "1 : Creer un compte " << '\n';
        std::cout << "2 : Se Connecter a un compte existant " << '\n';
        std::cout << "3 : Supprimer un compte existant " << '\n';
        std::cout << "4 : <Admin> Reset Data" << '\n';
        std::cout << "0 : Quitter l'application " << '\n';
        std::cout.flush();

        if (!(std::cin >> rep_init)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            rep_init = "-1";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(rep_init == "1"){
            std::cout << "\n--- Menu Creation de compte ---" << '\n';
            std::cout << "Entrez votre nom : " << '\n';
            std::cout.flush();
            std::getline(std::cin, nom);

            // Vérification de l'existence du compte
            bool compte_existant = false;
            for (const auto& user : users) {
                if (user.getUsername() == nom) {
                    compte_existant = true;
                    std::cout << "Un compte avec ce nom existe deja." << '\n';
                    break;
                }
            }

            if(!compte_existant){
                std::cout << "Entrez votre mot de passe : " << '\n';
                std::getline(std::cin, mdp); 
                std::cout.flush();
                users.push_back(User(nom, mdp));
                std::cout << "Compte cree avec succes !" << '\n';
                Save(users, tag);
            }
        }
        else if(rep_init == "2"){

            std::cout << "\n--- Menu Connexion ---" << '\n';
            std::cout << "Entrez votre nom : " << '\n';
            std::cout.flush();
            std::getline(std::cin, nom);
            std::cout << "Entrez votre mot de passe : " << '\n';
            std::cout.flush();
            std::getline(std::cin, mdp);
            
            connexion_successful = false;
            for(int i = 0; i < users.size(); i++){
                if(users[i].verifConnexion(nom, mdp)){
                    User_used = i;
                    ActualUser = &users[i];
                    std::cout << "Connexion reussie" << '\n';
                    connexion_successful = true;
                    break;
                } 
            }
            if(connexion_successful == false){
                std::cout << "Echec de la connexion, nom ou mot de passe incorrect" << '\n';
                continue;
            }
            
            rep_home = "-1";
            while(rep_home != "6"){

                std::cout << "\n--- Bienvenue " << ActualUser->getUsername() << " ---" << '\n';
                std::cout << "1 : Ajouter un mot de passe " << '\n';
                std::cout << "2 : Ajouter un label " << '\n';
                std::cout << "3 : Rechercher un mot de passe " << '\n';
                std::cout << "4 : Tester un mot de passe " << '\n';
                std::cout << "5 : Supprimer un mot de passe " << '\n';
                std::cout << "6 : Se deconnecter " << '\n';
                
                std::cout.flush();
                
                if (!(std::cin >> rep_home)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if(rep_home == "1"){

                    std::cout << "\n--- Menu Ajout de Mot de passe ---" << '\n';
                    std::cout << "Entrez l'application associee au mot de passe : " << '\n';
                    std::cout.flush();
                    std::getline(std::cin, nom);

                    std::cout << "\nType d'application : " << '\n';
                    std::cout << "1 : Email" << '\n';
                    std::cout << "2 : Bancaire" << '\n';
                    std::cout << "3 : Autre" << '\n';
                    std::cout.flush();
                    
                    std::string appType;
                    if(!(std::cin >> appType)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    // Utilisation de unique_ptr pour éviter les fuites mémoire
                    std::unique_ptr<Application> app = nullptr;
                    bool app_valide = false;
                        
                    if(appType == "1") {
                        std::string email;
                        std::cout << "Entrez l'email : " << '\n';
                        std::cout.flush();
                        std::getline(std::cin, email);
                        app = std::make_unique<EmailApplication>(nom, "Email", email);
                        if(app != nullptr && app->validate()) {
                            app->displayInfo();
                            app_valide = true;
                        }
                    }
                    else if(appType == "2") {
                        int cardNum, cvv;
                        std::string expDate;
                        std::cout << "Numero de carte : " << '\n';
                        std::cout.flush();
                        std::cin >> cardNum;
                        std::cout << "CVV : " << '\n';
                        std::cout.flush();
                        std::cin >> cvv;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Date d'expiration : " << '\n';
                        std::cout.flush();
                        std::getline(std::cin, expDate);
                        app = std::make_unique<BankApplication>(nom, "Bancaire", cardNum, cvv, expDate);
                        
                        // Correction : validation avant de marquer comme valide
                        if(app != nullptr && app->validate()) {
                            app->displayInfo();
                            app_valide = true;
                        } else {
                            std::cout << "Informations bancaires non valides" << '\n';
                        }
                    }
                    else if(appType == "3"){
                        std::cout << "Autre application creee" << '\n';
                        app_valide = true;
                    }
                    else {
                        std::cout << "Type non valide" << '\n';
                    }

                    // Continuer seulement si l'application est valide
                    if(app_valide) {

                        // Demander le mot de passe
                        std::cout << "\n1 : Entrer votre propre mot de passe " << '\n';
                        std::cout << "2 : Generer un mot de passe automatiquement" << '\n';
                        std::cout.flush();
                        
                        if(!(std::cin >> rep_mdp)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            rep_mdp = "-1";
                            continue;
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        // Variable pour stocker le mot de passe final
                        std::string password_final;

                        if(rep_mdp == "2"){
                            password_final = Mdp::mdpgenerator(16, true);
                            std::cout << "Voici votre nouveau mot de passe : " << password_final << '\n';
                        }
                        else if(rep_mdp == "1"){
                            std::cout << "Entrez votre mot de passe : " << '\n';
                            std::cout.flush();
                            std::getline(std::cin, password_final);
                        }
                        else {
                            std::cout << "Option invalide" << '\n';
                            continue;
                        }

                        //Demander le label
                        std::cout << "\nVoulez-vous ajouter un label a votre mot de passe ?" << '\n';
                        std::cout << "1 : Oui" << '\n';
                        std::cout << "2 : Non" << '\n';
                        std::cout.flush();
                        
                        std::string choix_label;
                        if(!(std::cin >> choix_label)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            choix_label = "2";
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        
                        std::string label_final = "";
                        
                        if(choix_label == "1"){
                            std::cout << "\nVoici la liste de tous les labels :" << '\n';
                            
                            if(tag.empty()){
                                std::cout << "(Aucun label disponible)" << '\n';
                            } else {
                                for (size_t i = 0; i < tag.size(); i++) {
                                    std::cout << "- " << tag[i].getName() << '\n';
                                }
                            }
                            
                            std::cout << "\nEntrez le nom du label a associer : " << '\n';
                            std::cout.flush();
                            std::getline(std::cin, etiquette);

                            bool found = false;
                            for (size_t i = 0; i < tag.size(); i++) {
                                if(etiquette == tag[i].getName()){
                                    label_final = tag[i].getName();
                                    found = true;
                                    break;
                                }
                            }
                            
                            if(!found){
                                std::cout << "Le label entrer ne correspond a aucun label existant." << '\n';
                            }
                        }

                        // Ajouter le mot de passe une seule fois avec le bon label
                        ActualUser->getMdp().push_back(Mdp(nom, password_final, label_final));
                        std::cout << "Mot de passe ajoute avec succes !" << '\n';
                        Save(users, tag);
                    }
                    // Le unique_ptr se libère automatiquement à la fin du scope
                }
                else if(rep_home == "2"){
                    std::cout << "\n--- Menu Ajout de Label ---" << '\n';
                    std::cout << "Entrez le nom du label a creer : ";
                    std::cout.flush();
                    std::getline(std::cin, nom);
                    std::cout << '\n';
                    
                    bool label_existant = false;
                    for (const auto& l : tag) {
                        if (l.getName() == nom) {
                            label_existant = true;
                            std::cout << "Un label avec ce nom existe deja." << '\n';
                            break;
                        }
                    }
                    
                    if(!label_existant){
                        tag.push_back(Label(nom));
                        std::cout << "Label cree avec succes !" << '\n';
                        Save(users, tag);
                        
                        std::cout << "\nListe des labels actuels :" << '\n';
                        for (size_t i = 0; i < tag.size(); ++i) {
                            std::cout << "- " << tag[i].getName() << '\n';
                        }
                    }
                }
                else if(rep_home == "3"){

                    do{
                        std::string recherche;

                        std::cout << "\n--- Menu Recherche ---" << '\n';
                        std::cout << "1 : Recherche par application" << '\n';
                        std::cout << "2 : Recherche par label " << '\n';
                        std::cout << "3 : Retour " << '\n';
                        std::cout.flush();
                        
                        if(!(std::cin >> rep_search)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            rep_search = "-1";
                            continue;
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if(rep_search == "1"){
                            std::cout << "Entrez le nom de l'application associee au mot de passe recherche : " << '\n';
                            std::cout.flush();
                            std::getline(std::cin, recherche);

                            bool found = false;
                            for(size_t i = 0; i < ActualUser->getMdp().size(); i++){
                                if(ActualUser->getMdp()[i].getName() == recherche){
                                    std::cout << "Mot de passe de l'application " << recherche 
                                             << " : " << ActualUser->getMdp()[i].getPassword() << '\n';
                                    found = true;
                                } 
                            }
                            
                            if (!found){
                                std::cout << "Aucun mot de passe trouve. Creez le mot de passe ou refaites une recherche." << '\n';
                            }
                        }
                        else if(rep_search == "2"){
                            std::cout << "Entrez le nom du label a rechercher : " << '\n';
                            std::cout.flush();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::getline(std::cin, recherche);
                            LabelSearch::searchByLabel(ActualUser->getMdp(), recherche);
                        }
                    } while(rep_search != "3");
                }
                else if(rep_home == "4"){
                    std::cout << "\n--- Testeur de mot de passe ---" << '\n';
                    std::cout << "Entrez le mot de passe a tester : " << '\n';
                    std::cout.flush();
                    std::getline(std::cin, mdp);
                        
                    PasswordTester tester(mdp);
                    tester.displayReport();
                    
                    if(tester.isStrong()){
                        std::cout << "Ce mot de passe est ACCEPTABLE !\n";
                    } else {
                        std::cout << "Ce mot de passe est TROP FAIBLE !\n";
                    }
                }
                else if(rep_home == "5"){
                    std::vector<Mdp>& mdpList = ActualUser->getMdp();
                    if (mdpList.empty()){
                        std::cout<<"Aucun mot de passe enregistré"<<'\n';
                        continue;
                    }
                    std::cout<<"\n---Menu de suppression de mot de passe---"<<'\n';
                    std::cout<<"Liste des mots de passe :"<<'\n';
                    for (size_t i = 0; i < mdpList.size(); i++){
                        std::cout<<"["<<i<<"] Application :"<<mdpList[i].getName()<<'\n';
                        if (!mdpList[i].getLabel().empty()){
                            std::cout<<"Label : "<<mdpList[i].getLabel()<<'\n';
                        }
                        std::cout<<'\n';
                    }
                    std::cout<<" "<<'\n';
                    std::cout<<"1 : Supprimer par index"<<'\n';
                    std::cout<<"2 : Supprimer par nom d'application"<<'\n';
                    std::cout<<"3 : Retour"<<'\n';
                    std::cout.flush();

                    std::string choix_supp;
                    if(!(std::cin >> choix_supp)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        choix_supp = "3";
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (choix_supp == "1") {
                        std::cout << "Entrez l'index du mot de passe a supprimer: ";
                        std::cout.flush();
                        int index;
                        if (std::cin >> index) {
                            if (index >= 0 && index < static_cast<int>(mdpList.size())) {
                                std::string appName = mdpList[index].getName();
                                mdpList.erase(mdpList.begin() + index);
                                std::cout << "Mot de passe de '" << appName << "' supprime avec succes !\n";
                                Save(users, tag);
                            } else {
                                std::cout << "Index invalide!\n";
                            }
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    } 
                    else if (choix_supp == "2") {
                        std::cout << "Entrez le nom de l'application: ";
                        std::cout.flush();
                        std::getline(std::cin, nom);
                        
                        bool found = false;
                        for (size_t i = 0; i < mdpList.size(); i++) {
                            if (mdpList[i].getName() == nom) {
                                mdpList.erase(mdpList.begin() + i);
                                std::cout << "Mot de passe de '" << nom << "' supprime avec succes !\n";
                                Save(users, tag);
                                found = true;
                                break;
                            }
                        }
                        
                        if (!found) {
                            std::cout << "Aucun mot de passe trouve pour l'application '" << nom << "'.\n";
                }
            }
            }
        }
                
            // Fin de la connexion, réinitialisation des variables
            connexion_successful = false;
            rep_home = "-1";
            ActualUser = nullptr;
        }
        else if(rep_init == "3"){
            std::cout << "\n--- Menu Suppression de compte ---" << '\n';
            std::cout << "Entrez votre nom : " << '\n';
            std::cout.flush();
            std::getline(std::cin, nom);
            std::cout << "Entrez votre mot de passe : " << '\n';
            std::cout.flush();
            std::getline(std::cin, mdp);

            bool compte_trouve = false;
            for(size_t i = 0; i < users.size(); i++){
                if(users[i].verifConnexion(nom, mdp)){
                    users.erase(users.begin() + i);
                    ActualUser = nullptr;
                    std::cout << "Votre compte a bien ete supprime." << '\n';
                    Save(users, tag);
                    compte_trouve = true;
                    break;
                }
            }
            
            if(!compte_trouve){
                std::cout << "Nom ou mot de passe incorrect." << '\n';
            }
        }
        else if(rep_init == "4"){
            std::cout << "Reset de toutes les donnees en cours..." << '\n';
            users.clear();
            tag.clear();
            Save(users, tag);
            std::cout << "Toutes les donnees ont ete reinitialisees." << '\n';
        }
    }
    
    std::cout << "\n\nMerci de votre visite !!!" << '\n';
    return 0;
}