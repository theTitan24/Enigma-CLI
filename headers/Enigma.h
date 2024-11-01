// Local Headers
#include "Keyboard.h"
#include "Plugboard.h"
#include "Rotor.h"
#include "Reflector.h"

// System Headers
#include <iostream>

class Enigma {
    private:
        // All the components of the Machine as Objects
        Keyboard kb;
        Rotor rotor1;
        Rotor rotor2;
        Rotor rotor3;
        Reflector reflector;
        Plugboard pb;


    public:
        // Import the pointers to Plugboard, Rotors and Reflector, and set them to the objects
        Enigma(Plugboard *pb, Rotor *r1, Rotor *r2, Rotor *r3, Reflector *ref) {
            this->pb = *pb;
            rotor1 = *r1;
            rotor2 = *r2;
            rotor3 = *r3;
            reflector = *ref;
        }

        // Set the rotors
        void setRotors(std::string rotorConfig) {
            rotor1.rotateToLetter(toupper(rotorConfig[0]));
            rotor2.rotateToLetter(toupper(rotorConfig[1]));
            rotor3.rotateToLetter(toupper(rotorConfig[2]));
        }

        // Set the rings
        void setRings(int ringConfig[3])
        {
            rotor1.setRing(ringConfig[0]);
            rotor2.setRing(ringConfig[1]);
            rotor3.setRing(ringConfig[2]);
        }

        // Encodes a character
        char encipher(char ch) {

            // Rotate the Rotor(s)
            // Rotate all Rotors normally
            if(rotor2.reachedNotch() && rotor3.reachedNotch()) {
                rotor1.step();
                rotor2.step();
                rotor3.step();
            }
            // Enigma Double Step anomaly
            else if(rotor2.reachedNotch()) {
                rotor1.step();
                rotor2.step();
                rotor3.step();
            }
            // Rotation of Rotors 2 and 3
            else if(rotor3.reachedNotch()) {
                rotor2.step();
                rotor3.step();
            }
            // Normal case, where only one rotor rotates
            else {
                rotor3.step();
            }
            
            // Let's go through the encoding process in the machine
            ch = toupper(ch);                   // Convert ch to uppercase
            int signal = kb.encode(ch);         // Convert ch into signal

            signal = pb.encode(signal);         // Forward Pass through Plugboard

            signal = rotor3.encode(signal) ;    // Forward Pass through Rotor1
            signal = rotor2.encode(signal);     // Forward Pass through Rotor2
            signal = rotor1.encode(signal);     // Forward Pass through Rotor3

            signal = reflector.reflect(signal); // Reflects back

            signal = rotor1.decode(signal);     // Back pass through Rotor3
            signal = rotor2.decode(signal);     // Back pass through Rotor2
            signal = rotor3.decode(signal);     // Back pass through Rotor1

            signal = pb.decode(signal);         // Back pass through Plugboard
            // One pass is done

            return kb.decode(signal);           // Return the character
        }

};