#include <iostream>
#include <algorithm>

class Rotor {
    private:
        std::string alph;
        std::string right;
        std::string left;
        std::string notch;

    public:
        // Default Constructor
        Rotor() {
            alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            left = alph;
            right = left;
            notch = "A";
        }

        // Sets right as wiring
        Rotor(std::string wiring, std::string notch) {
            alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            left = alph;
            right = wiring;
            this->notch = notch;
        }

        // Encodes in sameway as plugboard
        int encode(int signal) {
            return left.find(right[signal]);
        }

        // Does the same in opposite direction
        int decode(int signal) {
            return right.find(left[signal]);
        }

        // Rotates the Rotor by a single step
        void step() {
            std::rotate(left.begin(), left.begin() + 1, left.end());
            std::rotate(right.begin(), right.begin() + 1, right.end());
        }
        
        // Rotates n number of steps forwards
        void step(int n) {
            for(int i = 0; i < n; i ++) {
                std::rotate(left.begin(), left.begin() + 1, left.end());
                std::rotate(right.begin(), right.begin() + 1, right.end());
            }
        }

        // Rotates the Rotor to a specific letter
        void rotateToLetter(char ch) {
            int n = left.find(ch);
            step(n);
        }

        // Method to check if it has reached notch
        bool reachedNotch() {
            if(left.substr(0, 1) == notch) {
                return true;
            }
            else {
                return false;
            }
        }

        // Method to set ring
        void setRing(int n) {
            // Rotate backwards
            step(26 - (n - 1));

            // Adjusts the notch postion
            int oldNotchIdx = alph.find(notch);
            notch = alph[(oldNotchIdx - n) % 26];
        }


        // Sample method to show the arrangements
        void show() {
            std::cout << left << std::endl;
            std::cout << right << std::endl << std::endl;
        }
};

