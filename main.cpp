// Local Headers
// #include "headers/Keyboard.h"
// #include "headers/Plugboard.h"
// #include "headers/Rotor.h"
// #include "headers/Reflector.h"
#include "headers/Enigma.h"

// System Headers
#include <iostream>

// Configurations of Rotors I through V
Rotor I("EKMFLGDQVZNTOWYHXUSPAIBRCJ", "Q");
Rotor II("AJDKSIRUXBLHWTMCQGZNPYFVOE", "E");
Rotor III("BDFHJLCPRTXVZNYEIWGAKMUSQO", "V");
Rotor IV("ESOVPZJAYQUIRHXLNFTGKDCMWB", "J");
Rotor V("VZBRGITYUPSDNHLXAWMJQOFECK", "Z");

// Reflector Combinations A, B and C
Reflector A("EJMZALYXVBWFCRQUONTSPIKHGD");
Reflector B("YRUHQSLDPXNGOKMIEBFZCWVJAT");
Reflector C("FVPJIAOYEDRZXWGCTKUQSBNMHL");

// Object for Keyboard / Lightboard
Keyboard kb;
// Plugboard pb;

// Now let's try to encode a letter
int main() {
    
    // Set plugboard
    Plugboard pb("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    std::string input, output = "";

    std::cout << "Please Enter the Message: " << std::endl;   
    std::getline(std::cin, input);

    Enigma enigma(&pb, &I, &II, &III, &B);

    char rotorConfig[3] = {'M', 'C', 'K'};
    enigma.setRotors(rotorConfig);

    int ringConfig[3] = {1, 2, 3};
    enigma.setRings(ringConfig);

    for(int i = 0; i < input.length(); i++) {
        if(isalpha(input[i])) {
            output.push_back(enigma.encipher(input[i]));
        }
        else {
            output.push_back(input[i]);
        }
    }

    std::cout << output << std::endl;
}