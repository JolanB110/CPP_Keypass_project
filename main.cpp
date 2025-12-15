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


int main(){
    std::vector<Data> data;

    User* ActualUser = nullptr;

    int User_used;
    std::vector<User> users;
    std::string nom,mdp,etiquette;
    //User ActualUser = User("","");
    Mdp motdepasse = Mdp("","");
    std::vector<Label> tag;
    users = Import();

    bool connexion_successful = false;

    std::string rep_init = "-1";
    std::string rep_home = "-1";
    std::string rep_mdp = "-1";
    std::string rep_search = "-1";

    while (rep_init!="0"){

        std::cout << "\n--- Menu Principal ---" << '\n';
        std::cout << "1 : Creer un compte " << '\n';
        std::cout << "2 : Se Connecter a un compte existant " << '\n';
        std::cout << "3 : Supprime un compte existant " << '\n';
        std::cout << "4 : <Admin> Reset Data" << '\n';
        std::cout << "0 : Quitter l'application " << '\n';

        if (!(std::cin >> rep_init)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        rep_init = "-1";
        continue;
        }

        if(rep_init=="1"){
            std::cout << "\n--- Menu Creation de compte ---" << '\n';
            std::cout << "Entree votre nom : " << '\n' ;
            std::cin >> nom;

            // Vérification de l'existence du compte
            bool compte_existant = false;
            for (const auto& user : users) {
                if (user.getUsername() == nom) {
                    compte_existant = true;
                    std::cout<<"Un compte avec ce nom existe deja."<<'\n';
                    break;
                }
            }

            if(!compte_existant){
                std::cout<<"Entrez votre mot de passe : "<<'\n';
                std::cin>>mdp;
                users.push_back(User(nom, mdp));
                std::cout<<"Compte cree avec succes !"<<'\n';
                Save(users, tag);
            }
        }
        else if(rep_init=="2"){

            std::cout << "\n--- Menu Connexion ---" << '\n';
            std::cout << "Entree votre nom : " << '\n' ;
            std::cin >> nom;
            std::cout << "Entree votre mot de passe : " << '\n';
            std::cin >> mdp;

            connexion_successful = false;
            for(int i=0; i<users.size();i++){
                std::cout<< users[i].getUsername() << '\n';
                if(users[i].verifConnexion(nom, mdp)){
                    User_used = i;
                    ActualUser = &users[User_used];
                    std::cout << "Connexion reussie" << '\n';
                    connexion_successful = true;
                    break;
                } 
            }
            if(connexion_successful==false){
                std::cout << "Echec de la connexion, nom ou mot de passe incorrect" << '\n';
                    continue;
            }
            rep_home="-1";
            while(rep_home!="5"){

                std::cout << "\n--- Bienvenue "<< ActualUser->getUsername() << " ---" << '\n';
                std::cout << "1 : Ajouter un mot de passe " << '\n';
                std::cout << "2 : Ajouter un label " << '\n';
                std::cout << "3 : Rechercher un mot de passe " << '\n';
                std::cout << "4 : Tester un mot de passe " << '\n';
                std::cout << "5 : Se deconnecter " << '\n';
                std::cin >> rep_home;

                if(rep_home=="1"){

                    std::cout << "\n--- Menu Ajout de Mot de passe ---" << '\n';
                    std::cout << "Entree l application associe au mot de passe: " << '\n' ;
                    std::cin >> nom;
                    std::cout << "\nType d'application : " << '\n';
                    std::cout << "1 : Email" << '\n';
                    std::cout << "2 : Bancaire" << '\n';
                    std::cout << "3 : Autre" << '\n';
                    std::string appType;
                    std::cin >> appType;
                        
                    // Créer l'objet Application approprié
                    Application* app = nullptr;
                    bool app_valide = false;
                        
                    if(appType == "1") {
                        std::string email;
                        std::cout << "Entrez l email: " << '\n';
                        std::cin >> email;
                        app = new EmailApplication(nom, "Email", email);
                        if(app != nullptr && app->validate()) {
                            app->displayInfo();
                            app_valide = true;
                        }
                    }
                    else if(appType == "2") {
                        int cardNum, cvv;
                        std::string expDate;
                        std::cout << "Numero de carte: " << '\n';
                        std::cin >> cardNum;
                        std::cout << "CVV: " << '\n';
                        std::cin >> cvv;
                        std::cout << "Date d expiration: " << '\n';
                        std::cin >> expDate;
                        app = new BankApplication(nom, "Bancaire", cardNum, cvv, expDate);
                    }
                        
                    // Valider et afficher
                    if(app != nullptr && app->validate()) {
                        app->displayInfo();
                        app_valide = true;
                    }

                    // Toujours demander le mot de passe et le label, même si appType == "3"
                    else if(appType == "3"){
                        std::cout<<" Autre application creer" <<'\n';
                        app_valide = true;
                    }
                    else {
                        std::cout << "Type non valide" << '\n';
                    }
                    if(app_valide || appType == "3") {

                    std::cout<< "\n1 : Entree votre propre mot de passe " << '\n';
                    std::cout<< "2 : Generer un mot de passe automatiquement" << '\n';
                    std::cin >> rep_mdp;

                    if(rep_mdp=="2"){
                        std::string mdp = Mdp::mdpgenerator(16, true);
                        std::cout << "Voici votre nouveau mot de passe :" << mdp << '\n';
                        ActualUser->getMdp().push_back(Mdp(nom, mdp, ""));
                        Save(users, tag);
                    }
                    else{
                        std::cout<< "1 : Entree votre mot de passe " << '\n';
                        std::cin >> mdp;
                        ActualUser->getMdp().push_back(Mdp(nom, mdp, ""));
                    }

                    std::cout << "\n3 : Voulez vous ajouter un label a votre Mdp" << '\n';
                    std::cout << "4 : Non, pas la peine" << '\n';
                    std::cin >> etiquette;
                        
                    if(etiquette=="3"){

                        std::cout << "Voici la liste de tout les labels :" << '\n';
                        std::cout << "" << '\n';

                        for (int i=0; i < tag.size(); i++)
                        {
                            std::cout << tag[i].name << '\n';
                        }
                        std::cout << "" << '\n';
                        std::cout << "\nEntree le nom du label a associer a votre mot de passe : " << '\n' ;
                        std::cin >> etiquette;

                        bool found = false;
                        for (int i=0; i < tag.size(); i++)
                        {
                            if(etiquette==tag[i].name){
                                ActualUser->getMdp().pop_back(); //enlever le mdp sans label ajouté juste avant
                                ActualUser->getMdp().push_back(Mdp(nom, mdp, tag[i].name));
                                found = true;
                                break; //ajouter affichage label avec mdp pour vérifier si ça marche
                            }
                        }
                        if(!found){
                        std::cout << "Le Label rentrer ne correspond a aucun label existant !" << '\n' ;
                        }
                    }
                    Save(users, tag);
                    if(app != nullptr) {
                        delete app;
                    }
                }
                else if(rep_home=="2"){
                    std::cout << "\n--- Menu Ajout de Label ---" << '\n';
                    std::cout << "Entree le nom du label a creer : " << '\n' ;
                    std::cin >> nom;
                    std::cout << '\n' ;

                    //code en dessous a transformer en vérification d'existence

                    tag.push_back(Label(nom));
                    Save(users, tag);
                    for(int i=0; i<tag.size();i++){
                        std::cout << tag[i].getName() << '\n';
                    }
                    rep_home="-1";

                        //code au dessus a vérifier l'utilité 
                }

                else if(rep_home=="3"){

                    do{

                        std::string recherche;

                        std::cout << "\n--- Menu Recherche ---" << '\n';
                        std::cout << "1 : Recherche par application" << '\n' ;
                        std::cout << "2 : Recherche par label " << '\n' ;
                        std::cout << "3 : Retour " << '\n' ;
                        std::cin >> rep_search;

                        if(rep_search=="1"){

                            std::cout << "Entrer le nom de l application associe au mot de passe rechercher : " << '\n' ;
                            std::cin >> recherche;

                            for(int i=0; i<ActualUser->getMdp().size();i++){

                                if(ActualUser->getMdp()[i].getName() == recherche){

                                    std::cout << "Mot de passe de l application " << recherche << " : "<<ActualUser->getMdp()[i].getPassword() << '\n';

                                }else{
                                    std::cout << "Aucun mot de passe trouve, creer le mot de passe ou refaite une recherche" << '\n';
                                continue;
                                }
                            }
                        }

                        else if(rep_search=="2"){
                            std::cout << "Entrer le nom du label a rechercher : " << '\n';
                            std::cin >> recherche;
                            LabelSearch::searchByLabel(ActualUser->getMdp(), recherche);
                        }
                        // a peaufiner, peut être mieux a faire 
                    } while(rep_search !="3");
                }
                else if(rep_home=="4"){
                    std::cout << "\n--- Testeur de mot de passe ---" << '\n';
                    std::cout << "Entree le mot de passe a tester : " << '\n';
                    std::cin >> mdp;
                        
                    PasswordTester tester(mdp);
                    tester.displayReport();
                    
                    if(tester.isStrong()){
                        std::cout << "Ce mot de passe est ACCEPTABLE !\n";
                    } else {
                        std::cout << "Ce mot de passe est TROP FAIBLE !\n";
                    }
                }
            }
                
                //fin de la connexion, réinitialisation des variables
            connexion_successful = false;
            rep_home = "-1";
            ActualUser = nullptr;
            }
    }
        else if(rep_init=="3"){
            std::cout << "\n--- Menu Suppression de compte ---" << '\n';
            std::cout << "Entree votre nom : " << '\n' ;
            std::cin >> nom;
            std::cout<< "Entree votre mot de passe : " << '\n';
            std::cin >> mdp;

            for(int i=0; i<users.size();i++){
                std::cout<< users[i].getUsername() << '\n';
                if(users[i].verifConnexion(nom, mdp)){
                    users.erase(users.begin() + i);
                    ActualUser = nullptr;
                    std::cout << "Votre compte a bien ete supprime" << '\n';
                    Save(users, tag);
                    break;
                }
            }
        }
        else if(rep_init=="4"){
            std::cout << "Reset de toutes les donnees en cours..." << '\n';
            users.clear();
            tag.clear();
            Save(users, tag);
            std::cout << "Toutes les donnees ont ete reinitialisees." << '\n';
        }
    }
    std::cout << '\n' << "\nMerci de votre visite !!!" << '\n';
}
