#include <iostream>

class Keyboard {
    private:
        std::string alph;  // String containing the Alphabets

    public: 
        Keyboard() {
            alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        }

        // Encode method
        int encode(char letter) {
            return alph.find(toupper(letter)); // Returns the index of passed character
        }

        // Decode method
        char decode(int signal) {
            return alph[signal];               // Returns the character at passed index
        }
};

