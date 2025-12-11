#include "Save.hpp"
#include "Label.hpp"
#include <fstream>
#include <vector>

void Save(const std::vector<Comptes>& Comptes, const std::vector<Label> tag) {
    std::ofstream write_output("Save.dat");

    for (size_t i = 0; i < Comptes.size(); i++) {
        write_output << Comptes[i].name << " " << Comptes[i].password << " " << Comptes[i].label << "\n";
    }

    for (size_t i = 0; i < tag.size(); i++) {
        write_output << tag[i].getName() << "\n";
    }

    write_output.close();
}

/*

std::vector<Comptes> Import() {
    std::vector<Comptes> users;
    std::ifstream read_file("Save.dat");

    std::string name, password, label;
    while (read_file >> name >> password >> label) {
        users.push_back({name, password, label});
    }

    read_file.close();
    return users;
}

*/
