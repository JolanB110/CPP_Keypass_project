#ifndef LABEL_HPP
#define LABEL_HPP

#include <string>

class Label {

public:

    std::string name;      

    Label(const std::string& name); //constucteur 
    
    std::string getName() const { //méthode 
        return name; 
    }
};

#endif