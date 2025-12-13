#include "search_label.hpp"
#include <iostream>

void LabelSearch::searchByLabel(const std::vector<Mdp>& mdps, const std::string& searchLabel) {
    bool found = false;

    std::cout << "Resultats pour le label \"" << searchLabel << "\" :" << '\n';

    for (const auto& m : mdps) {
        if (m.getLabel() == searchLabel) {
            std::cout << "- Application : " << m.getName()
                      << " | Mot de passe : " << m.getPassword()
                      << " | Label : " << m.getLabel() << '\n';
            found = true;
        }
    }

    if (!found) {
        std::cout << "Aucun mot de passe trouve avec ce label." << '\n';
    }
}
