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


//BUG, quand rep==A ( par exemple ), une boucle infinie se lance, a regler.
//TOCHECK, a vérifier si on peut save un mdp sur un compte une fois le problème réglé.

int main(){
    std::vector<Data> data;

    User* ActualUser = nullptr;

    int User_used;
    std::vector<User> users;
    std::string nom,mdp,etiquette;
    //User ActualUser = User("","");
    Mdp motdepasse = Mdp("","");
    std::vector<Label> tag;

    bool connexion_successful = false;

    int rep_init = -1;
    int rep_home = -1;
    int rep_mdp = -1;
    int rep_search = -1;

    while (rep_init!=0){

        std::cout << "--- Menu Principal ---" << '\n';
        std::cout << "1 : Creer un compte " << '\n';
        std::cout << "2 : Se Connecter a un compte existant " << '\n';
        std::cout << "3 : Supprime un compte existant " << '\n';
        std::cout << "0 : Quitter l'application " << '\n';
        std::cin >> rep_init;

        if(rep_init==1){

            std::cout << "--- Menu Creation de compte ---" << '\n';
            std::cout << "Entree votre nom : " << '\n' ;
            std::cin >> nom;
            std::cout<< "Entree votre mot de passe : " << '\n';
            std::cin >> mdp;

            users.push_back(User(nom, mdp));

        }
        else if(rep_init==2){

            std::cout << "--- Menu Connexion ---" << '\n';
            std::cout << "Entree votre nom : " << '\n' ;
            std::cin >> nom;
            std::cout << "Entree votre mot de passe : " << '\n';
            std::cin >> mdp;
            
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
            else if(connexion_successful==true){
                while(rep_home!=6){

                    std::cout << "--- Bienvenue "<< ActualUser->getUsername() << " ---" << '\n';
                    std::cout << "1 : Ajouter un mot de passe " << '\n';
                    std::cout << "2 : Ajouter un label " << '\n';
                    std::cout << "3 : Rechercher un mot de passe " << '\n';
                    std::cout << "4 : Tester un mot de passe " << '\n';
                    std::cout << "5 : Generer rapport d'utilisation " << '\n';
                    std::cout << "6 : Se deconnecter " << '\n';
                    std::cin >> rep_home;

                    if(rep_home==1){

                        std::cout << "--- Menu Ajout de Mot de passe ---" << '\n';
                        std::cout << "Entree l application associe au mot de passe: " << '\n' ;
                        std::cin >> nom;
                        std::cout<< "1 : Entree votre propre mot de passe " << '\n';
                        std::cout<< "2 : Generer un mot de passe automatiquement" << '\n';
                        std::cin >> rep_mdp;

                        if(rep_mdp==2){
                            std::string mdp = motdepasse.mdpgenerator();
                            std::cout << "Voici votre nouveau mot de passe :" << mdp << '\n';
                            ActualUser->getMdp().push_back(Mdp(nom, mdp, ""));
                        }

                        else{
                            std::cout<< "1 : Entree votre mot de passe " << '\n';
                            std::cin >> mdp;
                            ActualUser->getMdp().push_back(Mdp(nom, mdp, ""));
                        }

                        std::cout << "3 : Voulez vous ajouter un label a votre Mdp" << '\n';
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
                            std::cout << "Entree le nom du label a associer a votre mot de passe : " << '\n' ;
                            std::cin >> etiquette;

                            for (int i=0; i < tag.size(); i++)
                            {
                                if(etiquette==tag[i].name){
                                    ActualUser->getMdp().push_back(Mdp(nom, mdp, tag[i].name));
                                    continue; //ajouter affichage label avec mdp pour vérifier si ça marche
                                }
                            }
                            std::cout << "Le Label rentrer ne correspond a aucun label existant !" << '\n' ;
                        }
                    }
                    else if(rep_home==2){
                        std::cout << "--- Menu Ajout de Label ---" << '\n';
                        std::cout << "Entree le nom du label a creer : " << '\n' ;
                        std::cin >> nom;
                        std::cout << '\n' ;

                        //code en dessous a transformer en vérification d'existence

                        tag.push_back(Label(nom));
                        for(int i=0; i<tag.size();i++){
                            std::cout << tag[i].getName() << '\n';
                        }
                        rep_home=-1;

                        //code au dessus a vérifier l'utilité 
                    }

                    else if(rep_home==3){

                        do{

                            std::string recherche;

                            std::cout << "--- Menu Recherche ---" << '\n';
                            std::cout << "1 : Recherche par application" << '\n' ;
                            std::cout << "2 : Recherche par label " << '\n' ;
                            std::cout << "3 : Retour " << '\n' ;
                            std::cin >> rep_search;

                            if(rep_search==1){

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

                            else if(rep_search==2){
                                std::cout << "Entrer le nom du label a rechercher : " << '\n';
                                std::cin >> recherche;
                                LabelSearch::searchByLabel(ActualUser->getMdp(), recherche);
                            }
                            // a peaufiner, peut être mieux a faire 
                        } while(rep_search !=3);
                    }

                    else if(rep_home==4){
                        std::cout << "--- Testeur de mot de passe ---" << '\n';
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
                }
                //fin de la connexion, réinitialisation des variables
                connexion_successful = false;
                rep_home = -1;
                User* ActualUser = nullptr;
        }
        else if(rep_init==3){

            std::cout << "--- Menu Suppression de compte ---" << '\n';
            std::cout << "Entree votre nom : " << '\n' ;
            std::cin >> nom;
            std::cout<< "Entree votre mot de passe : " << '\n';
            std::cin >> mdp;

            for(int i=0; i<users.size();i++){

                std::cout<< users[i].getUsername() << '\n';

                if(users[i].verifConnexion(nom, mdp)){

                    users.erase(users.begin() + i);
                    User* ActualUser = nullptr;
                    std::cout << "Votre compte a bien ete supprime" << '\n';
                    break;

                }
            }
        }
    }
    std::cout << '\n' << "Merci de votre visite !!!" << '\n';
}
