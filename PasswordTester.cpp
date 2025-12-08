#include "PasswordTester.hpp"
#include <iostream>
#include <algorithm>
#include <string>

PasswordTester::PasswordTester(const std::string& pwd)
    : password(pwd), score(0) {
    calculateScore();
}

bool PasswordTester::hasLowercase() const {
    for (char c : password) {
        if (c >= 'a' && c <= 'z') return true;
    }
    return false;
}

bool PasswordTester::hasUppercase() const {
    for (char c : password) {
        if (c >= 'A' && c <= 'Z') return true;
    }
    return false;
}

bool PasswordTester::hasDigits() const {
    for (char c : password) {
        if (c >= '0' && c <= '9') return true;
    }
    return false;
}

bool PasswordTester::hasSpecialChars() const {
    std::string specials = "!@#$%^&*()-_=+[]{}|;:,.<>?/~`";
    for (char c : password) {
        if (specials.find(c) != std::string::npos) return true;
    }
    return false;
}

bool PasswordTester::hasCommonPatterns() const {
    std::string pwd_lower = password;
    std::transform(pwd_lower.begin(), pwd_lower.end(), pwd_lower.begin(), ::tolower);
    
    std::string patterns[] = {
        "password", "123456", "qwerty", "abc", "000", "111",
        "admin", "letmein", "welcome", "monkey"
    };
    
    for (const auto& pattern : patterns) {
        if (pwd_lower.find(pattern) != std::string::npos) {
            return true;
        }
    }
    return false;
}

double PasswordTester::calculateEntropy() const {
    std::string unique_chars(password.begin(), password.end());
    std::sort(unique_chars.begin(), unique_chars.end());
    unique_chars.erase(std::unique(unique_chars.begin(), unique_chars.end()), 
                       unique_chars.end());
    return static_cast<double>(unique_chars.length()) / password.length();
}

void PasswordTester::calculateScore() {
    score = 0;
    
    // Longueur
    if (password.length() >= 8) score += 20;
    if (password.length() >= 12) score += 10;
    if (password.length() >= 16) score += 10;
    
    // Diversité
    if (hasLowercase()) score += 10;
    if (hasUppercase()) score += 10;
    if (hasDigits()) score += 10;
    if (hasSpecialChars()) score += 10;
    
    // Bonus complexité
    int types = 0;
    if (hasLowercase()) types++;
    if (hasUppercase()) types++;
    if (hasDigits()) types++;
    if (hasSpecialChars()) types++;
    if (types == 4) score += 10;
    
    // Entropie
    double entropy = calculateEntropy();
    if (entropy > 0.8) score += 5;
    if (entropy > 0.9) score += 5;
    
    // Pénalité motifs courants
    if (hasCommonPatterns()) {
        score = std::max(0, score - 30);
    }
    
    if (score > 100) score = 100;
    
    // Niveau
    if (score < 20) level = "Tres faible";
    else if (score < 40) level = "Faible";
    else if (score < 60) level = "Moyen";
    else if (score < 80) level = "Fort";
    else level = "Tres fort";
}

int PasswordTester::getScore() const {
    return score;
}

std::string PasswordTester::getLevel() const {
    return level;
}

bool PasswordTester::isStrong() const {
    return score >= 60;
}

void PasswordTester::displayReport() const {
    std::cout << "\n" << std::string(50, ' ') << "\n";
    std::cout << "ANALYSE DE MOT DE PASSE : \n";
    std::cout << "\n" << std::string(50, ' ') << "\n";
    
    std::cout << "Score : " << score << "/100\n";
    std::cout << "Force : " << level << "\n";
    std::cout << "Longueur : " << password.length() << " caracteres\n\n";
    
    std::cout << "Criteres satisfaits :\n";
    if (password.length() >= 8) std::cout << " Longueur >= 8\n";
    if (hasLowercase()) std::cout << " Minuscules\n";
    if (hasUppercase()) std::cout << " Majuscules\n";
    if (hasDigits()) std::cout << " Chiffres\n";
    if (hasSpecialChars()) std::cout << " Caracteres speciaux\n";
    
    std::cout << "\nCriteres manquants :\n";
    if (password.length() < 8) std::cout << " Longueur < 8\n";
    if (!hasLowercase()) std::cout << " Pas de minuscules\n";
    if (!hasUppercase()) std::cout << " Pas de majuscules\n";
    if (!hasDigits()) std::cout << " Pas de chiffres\n";
    if (!hasSpecialChars()) std::cout << " Pas de caracteres speciaux\n";
    
    if (hasCommonPatterns()) {
        std::cout << "\nATTENTION : Motif faible detecte !\n";
    }
    std::cout << "\n" << std::string(50, ' ') << "\n";
}
