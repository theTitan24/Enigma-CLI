#include <iostream>

class Plugboard {
    private:
        std::string base;   // Normal String
        std::string scrambled;   // Plugboard Configuration

    public:
        // Default Constructor
        Plugboard() {
            base = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            scrambled = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        }

        // Constructor with a complete String
        Plugboard(std::string config) {
            // To implement changing of scrambled to fit provided plugboard configuration

            // Rudimentary way to implement it. Hopefully I'll complete it later
            // This just takes the whole config as input
            base = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            scrambled = config;
        } 

        // The encode() and decode() functions do exactly what they say on the tin

        // Returns the index of the letter as swapped with base
        int encode(int signal) {
            return scrambled.find(base[signal]);
        }

        // Does the same in opposite direction
        int decode(int signal) {
            return base.find(scrambled[signal]);
        }
};