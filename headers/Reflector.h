#include <iostream>

class Reflector {
    private:
        std::string right;
        std::string left;

    public:
        // Default constructor, without any reflection
        Reflector() {
            left = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            right = left;
        }

        // Sets right as wiring
        Reflector(std::string wiring) {
            left = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            right = wiring;
        }

        // Encodes in sameway as plugboard
        int reflect(int signal) {
            return left.find(right[signal]);
        }
};
