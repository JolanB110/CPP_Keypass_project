#include "User.hpp"
#include <string>
#include <vector>
#include <iostream>

int main(){
    std::vector<User> users;
    std::string nom,mdp;
    User ActualUser = User("","");

    bool connexion_successful;

    int rep = -1;

    while (rep!=0)
    {
        std::cout << "--- Menu Principal ---" << '\n';
        std::cout << "1 : Creer un compte " << '\n';
        std::cout << "2 : Se Connecter a un compte existant " << '\n';
        std::cout << "3 : Supprime un compte existant " << '\n';
        std::cout << "0 : Quitter l'application " << '\n';
        std::cin >> rep;

        if(rep==1){

            std::cout << "--- Menu Creation de compte ---" << '\n';
            std::cout << "Entree votre nom : " << '\n' ;
            std::cin >> nom;
            std::cout<< "Entree votre mot de passe : " << '\n';
            std::cin >> mdp;

            users.push_back(User(nom, mdp));

        }
        else if(rep==2){

            std::cout << "--- Menu Connexion ---" << '\n';
            std::cout << "Entree votre nom : " << '\n' ;
            std::cin >> nom;
            std::cout << "Entree votre mot de passe : " << '\n';
            std::cin >> mdp;
            
            for(int i=0; i<users.size();i++){
                std::cout<< users[i].getUsername() << '\n';
                if(users[i].verifConnexion(nom, mdp)){
                    ActualUser = users[i];
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
                while(rep!=5){

                    std::cout << "--- Bienvenue "<< ActualUser.getUsername() << " ---" << '\n';
                    std::cout << "1 : Ajouter un mot de passe " << '\n';
                    std::cout << "2 : Rechercher un mot de passe " << '\n';
                    std::cout << "3 : Tester un mot de passe " << '\n';
                    std::cout << "4 : Generer rapport d'utilisation " << '\n';
                    std::cout << "5 : Se deconnecter " << '\n';
                    std::cin >> rep;

                    if(rep==1){

                        std::cout << "--- Menu Ajout de Mot de passe ---" << '\n';
                        std::cout << "Entree l application associe au mot de passe: " << '\n' ;
                        std::cin >> nom;
                        std::cout<< "1 : Entree votre mot de passe " << '\n';
                        std::cout<< "2 : Generer un mot de passe " << '\n';
                        std::cin >> mdp;

                        if(mdp=="2"){
                            //mdp = mdpgenerator() <<< générer mdp aléatoire
                            std::cout << "Voici votre nouveau mot de passe :" << mdp <<'\n';
                            //enregistrer mdp
                        }

                        else{
                            //enregistre mdp
                        }
                    }

                    else if(rep==2){

                        while(rep!=3){
                            std::cout << "--- Menu Recherche ---" << '\n';
                            std::cout << "1 : Recherche par application : " << '\n' ;
                            std::cout << "2 : Recherche par label : " << '\n' ;
                            std::cout << "3 : Retour : " << '\n' ;
                            std::cin >> rep;

                            if(rep==1){
                                //recherche par application : recherche_ecrite()
                            }

                            else if(rep==2){
                                //recherche par label : recherche_label()
                            }
                        }
                    }

                    else if(rep==3){
                        //tester un mot de passe
                    }
                }
        }
        else if(rep==3){

            std::cout << "--- Menu Suppression de compte ---" << '\n';
            std::cout << "Entree votre nom : " << '\n' ;
            std::cin >> nom;
            std::cout<< "Entree votre mot de passe : " << '\n';
            std::cin >> mdp;

            for(int i=0; i<users.size();i++){
                std::cout<< users[i].getUsername() << '\n';
                if(users[i].verifConnexion(nom, mdp)){
                    users.erase(users.begin() + i);
                    std::cout << "Votre compte a bien ete supprime" << '\n';
                    break;
                }
            }
        }
    }
    std::cout << '\n' << "Merci de votre visite !!!" << '\n';
}
}