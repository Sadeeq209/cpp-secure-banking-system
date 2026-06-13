#include "Encryption.h"
#include <string>

using namespace std;

// simple DJB2 hash algorithm used to convert input into a fixed numeric string
// this is a one way function (cannot be reversed back to original data)
string Encryption::hash(string data) {
    unsigned long h = 5381;

    // iterate through each character and build hash value
    for (char c : data) {
        h = ((h << 5) + h) + c; // h * 33 + c (DJB2 formula)
    }

    // convert final numeric hash to string for storage in file
    return to_string(h);
}