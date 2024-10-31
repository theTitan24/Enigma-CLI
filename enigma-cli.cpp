// Local Headers
#include "headers/Enigma.h"

// System Headers
#include <iostream>


// ============================================================

/*
    The following section includes creation of some objects,
    which correspond to the Historical parts of the Enigma
    namely:
        1. Rotors I through V
        2. Reflectors A, B and C
        3. Keyboard / Lampboard
*/

// Configurations of Historical Rotors I through V
Rotor I("EKMFLGDQVZNTOWYHXUSPAIBRCJ", "Q");
Rotor II("AJDKSIRUXBLHWTMCQGZNPYFVOE", "E");
Rotor III("BDFHJLCPRTXVZNYEIWGAKMUSQO", "V");
Rotor IV("ESOVPZJAYQUIRHXLNFTGKDCMWB", "J");
Rotor V("VZBRGITYUPSDNHLXAWMJQOFECK", "Z");

// Reflector Combinations A, B and C
Reflector A("EJMZALYXVBWFCRQUONTSPIKHGD");
Reflector B("YRUHQSLDPXNGOKMIEBFZCWVJAT");
Reflector C("FVPJIAOYEDRZXWGCTKUQSBNMHL");

// Object for Keyboard / Lampboard
Keyboard kb;

// ==========================================================

/*
    The following sections includes some variables which we will
    use to configure our Enigma machine
*/

// String to store plugboard configurationi
std::string plugboardConfig;

// Pointers to Respective rotors (To be used later)
Rotor* rotors[3];

// String to store Rotor configuration
std::string rotorConfig;

// int Array to store Ring configuration
int ringConfig[3];

// Pointer to the Used Reflector
Reflector* reflector;

// ===========================================================

/*
    Structure of Program (bottom-up) :
        1. int main(): Main method which will do the encoding / decoding stuff;
        2. void configure(): Will configure the variables to create an Enigma machine
        3. (optional, TBD later) std::string createPlugConfig(): This will simplify the plugboard config
*/

void configure() {
    std::cout << "--- Configuration Phase ---" << std::endl << "Please Enter the Following information:- " << std::endl;

    // Input Plugboard Configuration
    std::cout << "\n--- Plugboard ---" << "\nPlease Enter Plugboard Configuration: " << std::endl;
    std::cin >> plugboardConfig;
    if(plugboardConfig.length() != 26) {    // Checks for improper plugboard config
        std::cout << "Using No Plugs (Empty / Incorrect Configuration)..." << std::endl;
        plugboardConfig = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }

    // Input the Rotors to be used
    std::string rotorName;  // String to store the Rotor name
    std::cout << "\n--- Rotors ---" << "\n(Enter Roman Numerals I through V in Uppercase)" << std::endl;
    
    // Configure each rotor from user input
    for(int i = 0; i < 3; i ++) {
        std::cout << "Rotor " << (i + 1) << ": ";
        std::cin >> rotorName;

        if(rotorName == "I") {
            rotors[i] = &I;
        }
        else if(rotorName == "II") {
            rotors[i] = &II;
        }
        else if(rotorName == "III") {
            rotors[i] = &III;
        }
        else if(rotorName == "IV") {
            rotors[i] = &IV;
        }
        else if(rotorName == "V") {
            rotors[i] = &V;
        }
        else {
            std::cout << "Invalid Input. Using Default Rotor I..." << std::endl;
            rotors[i] = &I;
        }
    }

    // Set the rotor position
    std::cout << "\nRotor Position (Three Letters without space): ";
    std::cin >> rotorConfig;

    // Ring settings
    std::cout << "\nRing Settings (Three Numbers seperated by space): ";
    for(int i = 0; i < 3; i ++) {
        std::cin >> ringConfig[i];
    }

    // Input the Reflector
    char reflectorName;     // Reflector to be used
    std::cout << "\n--- Reflector ---" << std::endl;
    std::cout << "Reflector Name (A, B or C): ";
    std::cin >> reflectorName;
    switch (toupper(reflectorName)) {
        case 'A':
            reflector = &A;
            break;
        
        case 'B':
            reflector = &B;
            break;

        case 'C':
            reflector = &C;
            break;

        default:
            std::cout << "Using Default Reflector (B)...";
            reflector = &B;
            break;
    }
}

int main() {

    configure();    // Configure the variables

    Plugboard pb(plugboardConfig);  // Create the Plugboard;

    Enigma enigma(&pb, rotors[0], rotors[1], rotors[2], reflector); // Create the Enigma Machine
    enigma.setRotors(rotorConfig);  // Set the Rotor Postions
    enigma.setRings(ringConfig);    // Set the Ring Postions
    

    std::cout << "\n--- Encoding Phase ---" << std::endl;

    encode: // Encode block to code every message
        std::string input, output = ""; // Variables to store the input and output

        std::cin.clear();               // Clear the cin buffer
        std::cin.ignore(1000, '\n');    // Ignaore all characters till newline
        std::cout << "\nPlease Enter the Message: " << std::endl;   
        std::getline(std::cin, input);  // Input the message

        for(int i = 0; i < input.length(); i++) {               // Loops through every character
            if(isalpha(input[i])) {                             // Checks if it is an alphabet
                output.push_back(enigma.encipher(input[i]));    // Encodes and pushes it into output string
            }
            else {
                output.push_back(input[i]);                     // Pushes back the numbers and special characters
            }
        }

        std::cout << "\n" << output << std::endl;               // Display the output

    char op;
    std::cout << "\nContinue Encoding (With current settings) [y/n]? ";
    std::cin >> op;     // Checks if needed to go for another pass

    if(tolower(op) == 'y') {
        goto encode;    // Goes back to encode block
    }

    return 0;           // Ends successfully
}