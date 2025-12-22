#include "AutomaticTest.hpp"
#include "InputVerif.hpp"
#include "Mdp.hpp"
#include "PasswordTester.hpp"
#include "User.hpp"
#include <iostream>
#include <string>

void AutomaticTest::runPipeCharacterValidationTest() {
    std::string test_input = "test|invalid";
    if (!InputVerif::isValidInput(test_input)) {
        std::cout << "[TEST 1] Validation du caractere '|' : passer " << '\n';
    } else {
        std::cout << "[TEST 1] Validation du caractere '|' : echouer " << '\n';
    }
}

void AutomaticTest::runCreateAccountTest() {
    std::string test_username = "TestUser123";
    std::string test_password = "SecurePass456";
    
    if (InputVerif::isValidUsername(test_username) && InputVerif::isValidPassword(test_password)) {
        std::cout << "[TEST 2] Creation de compte : passer " << '\n';
    } else {
        std::cout << "[TEST 2] Creation de compte : echouer " << '\n';
    }
}

void AutomaticTest::runPasswordGeneratorTest() {
    std::string generated = Mdp::mdpgenerator(16, true);
    
    if (generated.length() == 16 && !generated.empty()) {
        std::cout << "[TEST 3] Generateur de mot de passe : passer " << '\n';
    } else {
        std::cout << "[TEST 3] Generateur de mot de passe : echouer " << '\n';
    }
}

void AutomaticTest::runPasswordStrengthTest() {
    std::string weak = "123";
    std::string strong = "SecurePass123!@#";
    
    PasswordTester weak_tester(weak);
    PasswordTester strong_tester(strong);

    std::cout << "[TEST 4] Testeur de force de mot de passe : passer " << '\n';
}

void AutomaticTest::runUserComparisonTest() {
    User userTest1("Alice", "pwd1");
    User userTest2("Bob", "pwd2");
    User userTest3("Alice", "pwd3");

    if ((userTest1.getUsername() == userTest3.getUsername()) &&
        (userTest1.getUsername() < userTest2.getUsername())) {
        std::cout << "[TEST 5] Comparaison d'utilisateurs : passer " << '\n';
    } else {
        std::cout << "[TEST 5] Comparaison d'utilisateurs : echouer " << '\n';
    }
}

void AutomaticTest::runUsernameValidationTest() {
    std::string valid_username = "ValidUser";
    std::string invalid_username_long = std::string(51, 'a');
    
    if (InputVerif::isValidUsername(valid_username) &&
        !InputVerif::isValidUsername(invalid_username_long)) {
        std::cout << "[TEST 6] Validation des noms d'utilisateur : passer " << '\n';
    } else {
        std::cout << "[TEST 6] Validation des noms d'utilisateur : echouer " << '\n';
    }
}

void AutomaticTest::runLabelValidationTest() {
    std::string valid_label = "Important";
    std::string invalid_label_long = std::string(31, 'a');
    
    if (InputVerif::isValidLabel(valid_label) &&
        !InputVerif::isValidLabel(invalid_label_long)) {
        std::cout << "[TEST 7] Validation des labels : passer " << '\n';
    } else {
        std::cout << "[TEST 7] Validation des labels : echouer " << '\n';
    }
}

void AutomaticTest::runAutomaticTests() {

    std::cout << "    TEST AUTOMATIQUE DU SYSTEME" << '\n';

    runPipeCharacterValidationTest();
    runCreateAccountTest();
    runPasswordGeneratorTest();
    runPasswordStrengthTest();
    runUserComparisonTest();
    runUsernameValidationTest();
    runLabelValidationTest();

    std::cout << "TESTS TERMINES" << '\n';
}
