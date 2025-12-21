#ifndef AUTOMATICTEST_HPP
#define AUTOMATICTEST_HPP

class AutomaticTest{
public:
    static void runAutomaticTests();

private:
    static void runPipeCharacterValidationTest();
    static void runCreateAccountTest();
    static void runPasswordGeneratorTest();
    static void runPasswordStrengthTest();
    static void runUsernameValidationTest();
    static void runLabelValidationTest();
};

#endif