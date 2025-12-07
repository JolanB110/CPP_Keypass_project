#ifndef PASSWORDTESTER_HPP
#define PASSWORDTESTER_HPP

#include <string>

class PasswordTester {
private:
    std::string password;
    int score;
    std::string level;
    
    void calculateScore();
    bool hasLowercase() const;
    bool hasUppercase() const;
    bool hasDigits() const;
    bool hasSpecialChars() const;
    bool hasCommonPatterns() const;
    double calculateEntropy() const;
    
public:
    PasswordTester(const std::string& pwd);
    
    int getScore() const;
    std::string getLevel() const;
    bool isStrong() const;
    
    void displayReport() const;
};

#endif
