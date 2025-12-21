#ifndef INPUTVERIF_HPP
#define INPUTVERIF_HPP

#include <string>

class InputVerif {
public:
    static bool isValidInput(const std::string& input);
    static std::string getValidatedInput(const std::string& prompt = "");

    static bool isValidUsername(const std::string& username);
    static bool isValidPassword(const std::string& password);
    static bool isValidLabel(const std::string& label);
};

#endif