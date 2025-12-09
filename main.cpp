#include "User.hpp"
#include "Mdp.hpp"
#include "PasswordTester.hpp"
#include <string>
#include <vector>
#include <iostream>

//BUG, quand rep==A ( par exemple ), une boucle infinie se lance, a regler.

int main(){
    std::vector<User> users;
    std::string nom,mdp;
    User ActualUser = User("","");
    Mdp motdepasse = Mdp("","");

    bool connexion_successful = false;

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
                        std::cout<< "1 : Entree votre propre mot de passe " << '\n';
                        std::cout<< "2 : Generer un mot de passe automatiquement" << '\n';
                        std::cin >> rep;

                        if(rep==2){
                            std::string mdp = motdepasse.mdpgenerator();
                            std::cout << "Voici votre nouveau mot de passe :" << mdp << '\n';
                            ActualUser.getMdp().push_back(Mdp(nom, mdp));
                        }

                        else{
                            std::cout<< "1 : Entree votre mot de passe " << '\n';
                            std::cin >> mdp;
                            ActualUser.getMdp().push_back(Mdp(nom, mdp));
                        }
                    }

                    else if(rep==2){

                        while(rep!=3){

                            std::string recherche;

                            std::cout << "--- Menu Recherche ---" << '\n';
                            std::cout << "1 : Recherche par application" << '\n' ;
                            std::cout << "2 : Recherche par label " << '\n' ;
                            std::cout << "3 : Retour " << '\n' ;
                            std::cin >> rep;

                            if(rep==1){

                                std::cout << "Entrer le nom de l application associe au mot de passe rechercher : " << '\n' ;
                                std::cin >> recherche;

                                for(int i=0; i<ActualUser.getMdp().size();i++){

                                    if(ActualUser.getMdp()[i].getName() == recherche){

                                        std::cout << "Mot de passe de l application " << recherche << " : "<<ActualUser.getMdp()[i].getPassword() << '\n';

                                    }else{
                                        std::cout << "Aucun mot de passe trouve, creer le mot de passe ou refaite une recherche" << '\n';
                                    continue;
                                    }
                                }

                            }

                            else if(rep==2){
                                //recherche par label : recherche_label()
                            }
                        }
                    }

                    else if(rep==3){
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
                    ActualUser = User("","");
                    std::cout << "Votre compte a bien ete supprime" << '\n';
                    break;

                }
            }
        }
    }
    std::cout << '\n' << "Merci de votre visite !!!" << '\n';
}
