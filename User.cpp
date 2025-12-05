#include "User.hpp"

User::User(const std::string& username, const std::string& masterPassword)
    : username(username), masterPassword(masterPassword)
{

}

bool User::verifConnexion(const std::string& EnterName, const std::string& EnterPassword){
    return (EnterName == username && EnterPassword == masterPassword);
}
