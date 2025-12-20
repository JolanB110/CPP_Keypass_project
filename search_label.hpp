#ifndef LABELSEARCH_HPP
#define LABELSEARCH_HPP

#include <string>
#include <vector>
#include "Mdp.hpp"

//recherche tous les mots de passe d'un utilisateur associés à un label donné.
class LabelSearch {
public:
    //affiche tous les Mdp dont le label == searchLabel
    static void searchByLabel(const std::vector<Mdp>& mdps, const std::string& searchLabel);
};

#endif
