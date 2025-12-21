#include "User.hpp"
#include "Save.hpp"
#include "Mdp.hpp"
#include "Label.hpp"
#include "Application.hpp"
#include "PasswordTester.hpp"
#include "search_label.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <memory>

//fonctions de validation

bool isValidInput(const std::string& input) {
    if (input.find('|') != std::string::npos) {
        std::cout << "ERREUR : Le caractere '|' est interdit (reserve pour import/export) !" << '\n';
        return false;
    }
    return true;
}

std::string getValidatedInput(const std::string& prompt = "") {
    std::string input;
    if (!prompt.empty()) {
        std::cout << prompt;
        std::cout.flush();
    }
    
    if (!std::getline(std::cin, input)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return "";
    }

    if (!isValidInput(input)) {
        return "";
    }

    return input;
}

bool isValidUsername(const std::string& username) {
    if (username.empty()) {
        std::cout << "ERREUR : Le nom d'utilisateur ne peut pas etre vide !" << '\n';
        return false;
    }
    if (username.length() > 50) {
        std::cout << "ERREUR : Le nom d'utilisateur est trop long (max 50 caracteres) !" << '\n';
        return false;
    }
    return isValidInput(username);
}

bool isValidPassword(const std::string& password) {
    if (password.empty()) {
        std::cout << "ERREUR : Le mot de passe ne peut pas etre vide !" << '\n';
        return false;
    }
    if (password.length() < 4) {
        std::cout << "ERREUR : Le mot de passe doit contenir au moins 4 caracteres !" << '\n';
        return false;
    }
    return isValidInput(password);
}

bool isValidLabel(const std::string& label) {
    if (label.empty()) {
        std::cout << "ERREUR : Le label ne peut pas etre vide !" << '\n';
        return false;
    }
    if (label.length() > 30) {
        std::cout << "ERREUR : Le label est trop long (max 30 caracteres) !" << '\n';
        return false;
    }
    return isValidInput(label);
}

//implémentation de fonctions de tests automatiques faite avec l'IA

void runPipeCharacterValidationTest() {
    std::string test_input = "test|invalid";
    if (!isValidInput(test_input)) {
        std::cout << "[TEST 1] Validation du caractere '|' : passer " << '\n';
    } else {
        std::cout << "[TEST 1] Validation du caractere '|' : echouer " << '\n';
    }
}

void runCreateAccountTest() {
    std::string test_username = "TestUser123";
    std::string test_password = "SecurePass456";
    
    if (isValidUsername(test_username) && isValidPassword(test_password)) {
        std::cout << "[TEST 2] Creation de compte : passer " << '\n';
    } else {
        std::cout << "[TEST 2] Creation de compte : echouer " << '\n';
    }
}

void runPasswordGeneratorTest() {
    std::string generated = Mdp::mdpgenerator(16, true);
    
    if (generated.length() == 16 && !generated.empty()) {
        std::cout << "[TEST 3] Generateur de mot de passe : passer " << '\n';
    } else {
        std::cout << "[TEST 3] Generateur de mot de passe : echouer " << '\n';
    }
}

void runPasswordStrengthTest() {
    std::string weak = "123";
    std::string strong = "SecurePass123!@#";
    
    PasswordTester weak_tester(weak);
    PasswordTester strong_tester(strong);
    
    std::cout << "[TEST 4] Testeur de force de mot de passe : passer " << '\n';
}

void runUsernameValidationTest() {
    std::string valid_username = "ValidUser";
    std::string invalid_username_long = std::string(51, 'a');
    
    if (isValidUsername(valid_username) && !isValidUsername(invalid_username_long)) {
        std::cout << "[TEST 5] Validation des noms d'utilisateur : passer " << '\n';
    } else {
        std::cout << "[TEST 5] Validation des noms d'utilisateur : echouer " << '\n';
    }
}

void runLabelValidationTest() {
    std::string valid_label = "Important";
    std::string invalid_label_long = std::string(31, 'a');
    
    if (isValidLabel(valid_label) && !isValidLabel(invalid_label_long)) {
        std::cout << "[TEST 6] Validation des labels : passer " << '\n';
    } else {
        std::cout << "[TEST 6] Validation des labels : echouer " << '\n';
    }
}

void runAutomaticTests() {

    std::cout << "    TEST AUTOMATIQUE DU SYSTEME" << '\n';

    
    runPipeCharacterValidationTest();
    runCreateAccountTest();
    runPasswordGeneratorTest();
    runPasswordStrengthTest();
    runUsernameValidationTest();
    runLabelValidationTest();

    std::cout << "TESTS TERMINES" << '\n';

}

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
        std::cout << "4 : Reset Data" << '\n';
        std::cout << "5 : Tests automatiques " << '\n';
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
                    
                    if(ActualUser->is2FAEnabled()) {
                        std::string code2FA;
                        std::string expected2FA = ActualUser->get2FACode();
                        std::cout << "\n--- Authentification 2FA ---" << '\n';
                        std::cout << "2FA activé. Entrez votre code 2FA : " << '\n';
                        std::cout << "(Code pour test: " << expected2FA << ")" << '\n';
                        std::cout.flush();
                        std::getline(std::cin, code2FA);
                        
                        if(ActualUser->verify2FA(code2FA)) {
                            std::cout << "Connexion reussie avec 2FA !" << '\n';
                            connexion_successful = true;
                            break;
                        } else {
                            std::cout << "Code 2FA incorrect !" << '\n';
                            ActualUser = nullptr;
                            continue;
                        }
                    } else {
                        std::cout << "Connexion reussie" << '\n';
                        connexion_successful = true;
                        break;
                    }
                }
            }

            if(connexion_successful == false){
                std::cout << "Echec de la connexion, nom ou mot de passe incorrect" << '\n';
                continue;
            }

            rep_home = "-1";
            while(rep_home != "8"){
                std::cout << "\n--- Bienvenue " << ActualUser->getUsername() << " ---" << '\n';
                std::cout << "1 : Ajouter un mot de passe " << '\n';
                std::cout << "2 : Ajouter un label " << '\n';
                std::cout << "3 : Rechercher un mot de passe " << '\n';
                std::cout << "4 : Tester un mot de passe " << '\n';
                std::cout << "5 : Supprimer un mot de passe " << '\n';
                std::cout << "6 : Supprimer un label " << '\n';
                std::cout << "7 : Gerer 2FA " << '\n';
                std::cout << "8 : Se deconnecter " << '\n';
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

                    bool found = false;
                    for(size_t i = 0; i < ActualUser->getMdp().size(); i++){
                        if(ActualUser->getMdp()[i].getName()== nom){
                            std::cout << "Attention : Un mot de passe pour cette application existe deja !" << '\n';
                            std::cout << "Supprimer l'ancien mot de passe ou changer le nom de l'application." << '\n';
                            found = true;
                            break;
                        }
                    }

                    if(found == true){
                        break;
                    }
                    std::cout << "\nType d'application : " << '\n';
                    std::cout << "1 : Email" << '\n';
                    std::cout << "2 : Bancaire" << '\n';
                    std::cout << "3 : Autre" << '\n';
                    std::cout.flush();

                    std::string appTypeStr;
                    if(!std::getline(std::cin, appTypeStr)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }

                    int appType = 0;
                    try {
                        appType = std::stoi(appTypeStr);
                    } catch(...) {
                        std::cout << "Veuillez entrer un nombre valide (1, 2 ou 3)" << std::endl;
                        continue;
                    }

                    std::unique_ptr<Application> app = nullptr;
                    bool app_valide = false;

                    if(appType == 1) {
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
                    else if(appType == 2) {
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

                        if(app != nullptr && app->validate()) {
                            app->displayInfo();
                            app_valide = true;
                        } else {
                            std::cout << "Informations bancaires non valides" << '\n';
                        }
                    }
                    else if(appType == 3){
                        std::cout << "Autre application creee" << '\n';
                        app_valide = true;
                    }
                    else {
                        std::cout << "Type non valide" << '\n';
                    }

                    if(app_valide) {
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

                        std::cout << "\nVoulez-vous ajouter un label a votre mot de passe ?" << '\n';
                        std::cout << "1 : Oui" << '\n';
                        std::cout << "2 : Non" << '\n';
                        std::cout.flush();

                        std::string choixLabelStr;
                        if(!std::getline(std::cin, choixLabelStr)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            choixLabelStr = "2";
                        }

                        int choixlabel = 2;
                        try {
                            choixlabel = std::stoi(choixLabelStr);
                        } catch(...) {
                            choixlabel = 2;
                        }

                        std::string label_final = "";

                        if(choixlabel == 1){
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

                        ActualUser->getMdp().push_back(Mdp(nom, password_final, label_final));
                        std::cout << "Mot de passe ajoute avec succes (chiffre) !" << '\n';
                        Save(users, tag);
                    }
                }
                else if(rep_home == "2"){
                    std::cout << "\n--- Menu Ajout de Label ---" << '\n';
                    std::cout << "Entrez le nom du label a creer : " << '\n';
                    std::cout.flush();
                    std::getline(std::cin, nom);
                    std::cout << '\n';

                    //vérifie s'il n'y a pas déjà un label avec ce nom
                    bool label_existant = false;
                    for (const auto& l : tag) {
                        if (l.getName() == nom) {
                            label_existant = true;
                            std::cout << "ERREUR : Un label avec ce nom existe deja !" << '\n';
                            std::cout << "Impossible de creer deux labels avec le meme nom." << '\n';
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
                        std::cout<<"Aucun mot de passe enregistre"<<'\n';
                        continue;
                    }

                    std::cout<<"\n---Menu de suppression de mot de passe---"<<'\n';
                    std::cout<<"Liste des mots de passe :"<<'\n';
                    for (size_t i = 0; i < mdpList.size(); i++){
                        std::cout<<"["<<i<<"] "<<mdpList[i].getName()<<'\n';
                    }

                    std::cout<<"\n1 : Supprimer par index"<<'\n';
                    std::cout<<"2 : Supprimer par nom"<<'\n';
                    std::cout<<"3 : Annuler"<<'\n';
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
                else if (rep_home == "6"){
                    if (tag.empty()){
                        std::cout<<"Aucun label a ete enregistre"<<'\n';
                        continue;
                    }

                    std::cout<<"\n---Menu de suppression de label---"<<'\n';
                    std::cout<<"Liste des labels :"<<'\n';
                    for (size_t i = 0; i < tag.size(); i++){
                        std::cout<<"["<<i<<"] "<<tag[i].getName()<<'\n';
                    }

                    std::cout<<"\n1 : Supprimer par index"<<'\n';
                    std::cout<<"2 : Supprimer par nom"<<'\n';
                    std::cout<<"3 : Annuler"<<'\n';
                    std::cout.flush();

                    std::string choix_supp_label;
                    if(!(std::getline(std::cin, choix_supp_label))) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        choix_supp_label = "3";
                    }
                    

                    if (choix_supp_label == "1") {
                        std::cout << "Entrez l'index du label a supprimer: ";
                        std::cout.flush();
                        int index;
                        if (std::cin >> index) {
                            if (index >= 0 && index < static_cast<int>(tag.size())) {
                                std::string labelName = tag[index].getName();
                                tag.erase(tag.begin() + index);
                                std::cout << "Label '" << labelName << "' supprime avec succes !\n";
                                Save(users, tag);
                            } else {
                                std::cout << "Index invalide!\n";
                            }
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    else if (choix_supp_label == "2") {
                        std::cout << "Entrez le nom du label: ";
                        std::cout.flush();
                        std::getline(std::cin, nom);

                        bool found = false;
                        for (size_t i = 0; i < tag.size(); i++) {
                            if (tag[i].getName() == nom) {
                                tag.erase(tag.begin() + i);
                                // Supprimer le label des mdp qui l'utilisent (TOUS les utilisateurs)
                                for (auto& user : users) {  // ← Boucle sur TOUS les users
                                    for (auto& mdpItem : user.getMdp()) {
                                        if (mdpItem.getLabel() == nom) {
                                            mdpItem.setLabel("");
                                        }
                                    }
                                }
                                std::cout << "Label '" << nom << "' supprime avec succes !\n";
                                Save(users, tag);
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            std::cout << "Aucun label trouve avec le nom '" << nom << "'.\n";
                        }
                    }
                }
                else if(rep_home == "7"){
                    std::cout << "\n--- Gestion 2FA ---" << '\n';
                    if(ActualUser->is2FAEnabled()) {
                        std::cout << "2FA est actuellement ACTIVE" << '\n';
                        std::cout << "Secret: " << ActualUser->get2FASecret() << '\n';
                        std::cout << "Code actuel: " << ActualUser->get2FACode() << '\n';
                        std::cout << "Voulez-vous la desactiver ? (1: Oui, 2: Non)" << '\n';
                        std::string choix2FA;
                        std::cin >> choix2FA;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(choix2FA == "1") {
                            ActualUser->disable2FA();
                            std::cout << "2FA desactivee." << '\n';
                            Save(users, tag);
                        }
                    } else {
                        std::cout << "2FA est actuellement INACTIVE" << '\n';
                        std::cout << "Voulez-vous l activer ? (1: Oui, 2: Non)" << '\n';
                        std::string choix2FA;
                        std::cin >> choix2FA;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(choix2FA == "1") {
                            ActualUser->enable2FA();
                            std::cout << "2FA activee ! Votre code secret est: " << ActualUser->get2FASecret() << '\n';
                            std::cout << "Conservez ce code en lieu sur." << '\n';
                            Save(users, tag);
                        }
                    }
                }
            }

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
        else if(rep_init == "5"){
            runAutomaticTests();
        }
    }
    std::cout << "\n\nMerci de votre visite !!!" << '\n';
    return 0;
}