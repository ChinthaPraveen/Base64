#include "Base64.h"
const char base64_chars[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
    '+', '/'
};

// Decoding look-up table
const char base64_decoding_table[256] = {
    ['A'] = 0,  ['B'] = 1,  ['C'] = 2,  ['D'] = 3,  ['E'] = 4,  ['F'] = 5,  ['G'] = 6,  ['H'] = 7, 
    ['I'] = 8,  ['J'] = 9,  ['K'] = 10, ['L'] = 11, ['M'] = 12, ['N'] = 13, ['O'] = 14, ['P'] = 15, 
    ['Q'] = 16, ['R'] = 17, ['S'] = 18, ['T'] = 19, ['U'] = 20, ['V'] = 21, ['W'] = 22, ['X'] = 23, 
    ['Y'] = 24, ['Z'] = 25, ['a'] = 26, ['b'] = 27, ['c'] = 28, ['d'] = 29, ['e'] = 30, ['f'] = 31, 
    ['g'] = 32, ['h'] = 33, ['i'] = 34, ['j'] = 35, ['k'] = 36, ['l'] = 37, ['m'] = 38, ['n'] = 39, 
    ['o'] = 40, ['p'] = 41, ['q'] = 42, ['r'] = 43, ['s'] = 44, ['t'] = 45, ['u'] = 46, ['v'] = 47, 
    ['w'] = 48, ['x'] = 49, ['y'] = 50, ['z'] = 51, ['0'] = 52, ['1'] = 53, ['2'] = 54, ['3'] = 55, 
    ['4'] = 56, ['5'] = 57, ['6'] = 58, ['7'] = 59, ['8'] = 60, ['9'] = 61, ['+'] = 62, ['/'] = 63
};

void base64_Encode(const char *data, char *encoded) {
    int i = 0, j = 0;
    int length = 0;
    char a3[3];
    char a4[4];

    // Calculate the length of the input data
    while (data[length] != '\0') {
        length++;
    }

    // Process input data three bytes at a time
    for (i = 0; i < length;) {
        // Load three bytes into a3 (pad with 0 if necessary)
        a3[0] = (i < length) ? data[i++] : 0;
        a3[1] = (i < length) ? data[i++] : 0;
        a3[2] = (i < length) ? data[i++] : 0;

        // Convert the three bytes into four Base64 indices
        a4[0] = (a3[0] & 0xfc) >> 2;
        a4[1] = ((a3[0] & 0x03) << 4) | ((a3[1] & 0xf0) >> 4);
        a4[2] = ((a3[1] & 0x0f) << 2) | ((a3[2] & 0xc0) >> 6);
        a4[3] = a3[2] & 0x3f;

        // Map each Base64 index to the corresponding character
        for (int index = 0; index < 4; index++) {
            encoded[j++] = base64_chars[a4[index]];
        }
    }

    // Add padding characters ('=') if necessary
    while (j % 4 != 0) {
        encoded[j++] = '=';
    }

    encoded[j] = '\0';  // Null-terminate the encoded string
}

void base64_Decode(const char *encoded, char *decoded) {
    int i = 0, j = 0;
    int length = 0;
    char a3[3];
    char a4[4];

    // Calculate the length of the encoded data (ignoring '=' padding)
    while (encoded[length] != '\0' && encoded[length] != '=') {
        length++;
    }

    // Process encoded data four characters at a time
    for (i = 0; i < length;) {
        // Load four characters into a4
        a4[0] = base64_decoding_table[(int)encoded[i++]];
        a4[1] = base64_decoding_table[(int)encoded[i++]];
        a4[2] = base64_decoding_table[(int)encoded[i++]];
        a4[3] = base64_decoding_table[(int)encoded[i++]];

        // Convert the four Base64 indices into three bytes
        a3[0] = (a4[0] << 2) | ((a4[1] & 0x30) >> 4);
        a3[1] = ((a4[1] & 0x0f) << 4) | ((a4[2] & 0x3c) >> 2);
        a3[2] = ((a4[2] & 0x03) << 6) | a4[3];

        // Store the decoded bytes
        for (int index = 0; index < 3 && (i - 1 - index) < length; index++) {
            decoded[j++] = a3[index];
        }
    }

    decoded[j] = '\0';  // Null-terminate the decoded string
}