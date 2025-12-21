#include "InputVerif.hpp"
#include <iostream>
#include <limits>

bool InputVerif::isValidInput(const std::string& input) {
    if (input.find('|') != std::string::npos) {
        std::cout << "ERREUR : Le caractere '|' est interdit (reserve pour import/export) !" << '\n';
        return false;
    }
    return true;
}

std::string InputVerif::getValidatedInput(const std::string& prompt) {
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

bool InputVerif::isValidUsername(const std::string& username) {
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

bool InputVerif::isValidPassword(const std::string& password) {
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

bool InputVerif::isValidLabel(const std::string& label) {
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
