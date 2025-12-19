#include "User.hpp"
#include <random>
#include <ctime> 
#include <cstdio>

std::string Encryption::encryptPassword(const std::string& password, int shift) {
    std::string encrypted = "";
    for (char c : password) {
        encrypted += static_cast<char>(c + shift);
    }
    return encrypted;
}

std::string Encryption::decryptPassword(const std::string& encrypted, int shift) {
    std::string decrypted = "";
    for (char c : encrypted) {
        decrypted += static_cast<char>(c - shift);
    }
    return decrypted;
}


void TwoFactor::enable() {
    //génère un secret aléatoire de 6 caractères
    std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, charset.length() - 1);
    
    secret = "";
    for (int i = 0; i < 6; i++) {
        secret += charset[dis(gen)];
    }
    
    enabled = true;
}

void TwoFactor::disable() {
    enabled = false;
    secret = "";
}

std::string TwoFactor::generateCode() {
    if (!enabled || secret.empty()) {
        return "";
    }
    
    //code basé sur le secret et le temps actuel
    unsigned long timestamp = std::time(nullptr) / 30;
    unsigned long code = 0;
    
    for (char c : secret) {
        code = (code * 31 + c) % 1000000;
    }
    
    code = (code + timestamp) % 1000000;
    
    char buffer[7];
    std::sprintf(buffer, "%06lu", code);
    return std::string(buffer);
}

bool TwoFactor::verifyCode(const std::string& userCode) {
    if (!enabled) {
        return true;
    }
    
    std::string correctCode = generateCode();
    
    //vérifie le code actuel
    if (userCode == correctCode) {
        return true;
    }
    
    //vérifie aussi le code de la période précédente (tolérance timing)
    unsigned long prevTimestamp = (std::time(nullptr) / 30) - 1;
    unsigned long prevCode = 0;
    
    for (char c : secret) {
        prevCode = (prevCode * 31 + c) % 1000000;
    }
    prevCode = (prevCode + prevTimestamp) % 1000000;
    
    char buffer[7];
    std::sprintf(buffer, "%06lu", prevCode);
    
    return (userCode == std::string(buffer));
}


User::User(const std::string& username, const std::string& masterPassword)
    : username(username), masterPassword(masterPassword)
{

}

bool User::verifConnexion(const std::string& EnterName, const std::string& EnterPassword){
    return (EnterName == username && EnterPassword == masterPassword);
}
