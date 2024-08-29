# Base64
This file contains encoding and decoding code for base64 format
# Base64 Encoding and Decoding

This project provides a simple implementation of Base64 encoding and decoding in C. Base64 is a binary-to-text encoding scheme that represents binary data in an ASCII string format. It is commonly used to encode data that needs to be stored and transferred over media that are designed to deal with text.

## Files

- **Base64.h**: Header file containing function declarations for Base64 encoding and decoding.
- **Base64.c**: Source file containing the implementation of Base64 encoding and decoding functions.

## Functions

### 1. `void base64_Encode(const char *data, char *encoded)`
This function encodes a given input string (`data`) into Base64 format and stores the result in the output string (`encoded`).

- **Parameters**:
  - `data`: The input string to be encoded.
  - `encoded`: The output buffer to store the Base64 encoded string. The buffer should be large enough to hold the encoded data.

- **Example Usage**:
  ```c
  char data[] = "Hello, World!";
  char encoded[256];  // Ensure this buffer is large enough
  base64_Encode(data, encoded);
  printf("Encoded: %s\n", encoded);

