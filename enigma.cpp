#include <iostream>
#include <string>

class enigmaClass {
private:
    const char reflector[27] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
    const char rotor_table[5][27] =
            {
                    "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
                    "AJDKSIRUXBLHWTMCQGZNPYFVOE",
                    "BDFHJLCPRTXVZNYEIWGAKMUSQO",
                    "ESOVPZJAYQUIRHXLNFTGKDCMWB",
                    "VZBRGITYUPSDNHLXAWMJQOFECK"
            };
    const char step_char[6] = "RFWKA"; // Royal Flags Wave Kings Above
    char plugBoard[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static char getLetterNum(char letter) {
        return (letter - 'A' + 26) % 26;
    }

    //[0] is the leftmost rotor
    int rotorChoice[3] = {0, 1, 4};//range from 0 to 4
    char ringSetting[3] = {'T', 'I', 'P'};//range from 'A' to 'Z'
    char messageKey[3] = {'C', 'R', 'Y'};//range from 'A' to 'Z'


    void rotorMove() {
        //double step
        if (messageKey[1] == getLetterNum(step_char[rotorChoice[1]] - 1) + 'A') {
            messageKey[0] = getLetterNum(messageKey[0] + 1) + 'A';
            messageKey[1] = getLetterNum(messageKey[1] + 1) + 'A';
            messageKey[2] = getLetterNum(messageKey[2] + 1) + 'A';
        }
            //single step
        else if (messageKey[2] == getLetterNum(step_char[rotorChoice[2]] - 1) + 'A') {
            messageKey[1] = getLetterNum(messageKey[1] + 1) + 'A';
            messageKey[2] = getLetterNum(messageKey[2] + 1) + 'A';
        }
            //only move the rightmost one
        else {
            messageKey[2] = getLetterNum(messageKey[2] + 1) + 'A';
        }
    }

    char rotorEncryptReverse(char input, int rotorNo) {
        int i;
        int delta = messageKey[rotorNo] - ringSetting[rotorNo];

        input = getLetterNum(input + delta) + 'A';
        for (i = 0; i < 26 && rotor_table[rotorChoice[rotorNo]][i] != input; ++i);
        input = i;
        return (input - delta + 26) % 26 + 'A';
    }

    char rotorEncrypt(char input, int rotorNo) {
        int delta = messageKey[rotorNo] - ringSetting[rotorNo];
        input = getLetterNum(input + delta);
        input = rotor_table[rotorChoice[rotorNo]][input];
        return getLetterNum(input - delta) + 'A';
    }

    char encryptChar(char input) {
        rotorMove();
        input = plugBoard[getLetterNum(input)];
        for (int i = 2; i > -1; --i) {
            input = rotorEncrypt(input, i);
        }
        input = reflector[getLetterNum(input)];
        for (int i = 0; i < 3; ++i) {
            input = rotorEncryptReverse(input, i);
        }
        input = plugBoard[getLetterNum(input)];
        return input;
    }

public:
    void setMessageKey(char mk0, char mk1, char mk2) {
        messageKey[0] = mk0;
        messageKey[1] = mk1;
        messageKey[2] = mk2;
    }

    void setRingSetting(char rs0, char rs1, char rs2) {
        ringSetting[0] = rs0;
        ringSetting[1] = rs1;
        ringSetting[2] = rs2;
    }

    void setRotorChoice(int rc0, int rc1, int rc2) {
        rotorChoice[0] = rc0 - 1;
        rotorChoice[1] = rc1 - 1;
        rotorChoice[2] = rc2 - 1;
    }

    char *getRotorChoice() {
        char *str = new char[4];
        str[0] = rotorChoice[0] + 1 + '0';
        str[1] = rotorChoice[1] + 1 + '0';
        str[2] = rotorChoice[2] + 1 + '0';
        str[3] = '\0';
        return str;
    }

    void setPlugBoard(char a, char b) {
        int i, j;
        for (i = 0; i < 26 && plugBoard[i] != a; ++i) {}
        for (j = 0; j < 26 && plugBoard[j] != b; ++j) {}
        plugBoard[i] = b;
        plugBoard[j] = a;
    }

    void encryptString(std::string &input) {
        for (int i = 0; i < input.length(); ++i) {
            input[i] = encryptChar(input[i]);
        }
    }
};