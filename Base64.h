#ifndef BASE64_H
#define BASE64_H
#include <Arduino.h>
#include<stdio.h>
#include <string.h>
void base64_Encode(char *data, char*encoded);
void base64_Decode(char *encoded, char *decoded);
#endif