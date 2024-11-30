#include <string.h>
#include <stdio.h>

void append(char* charArray, char newChar) {
    charArray[strlen(charArray)] = newChar;
}

char* longToString(long number, char* string) {
    sprintf(string, "%ld", number);
    return string; 
}

long exponent(int x, int b) {
    long output = 1;
    for(int i = 0; i < b; i++) {
        output *= x;
    }
    return output;
}

unsigned long toLong(char* charArray) {
    unsigned long convertedLong = 0;
    unsigned int element;
    for(int i = strlen(charArray) - 1; i >= 0; i--) {
        element = charArray[i];
        convertedLong += element * exponent(256, strlen(charArray) - i - 1);
    }
    return convertedLong;
}

unsigned long long toLongLong(char* charArray) {
    unsigned long long convertedLong = 0;
    unsigned int element;
    for(int i = strlen(charArray) - 1; i >= 0; i--) {
        element = charArray[i];
        convertedLong += element * exponent(256, strlen(charArray) - i - 1);
    }
    return convertedLong;
}

unsigned int toInt(char* charArray) {
    unsigned int convertedLong = 0;
    unsigned int element;
    for(int i = strlen(charArray) - 1; i >= 0; i--) {
        element = charArray[i];
        convertedLong += element * exponent(256, strlen(charArray) - i - 1);
    }
    return convertedLong;
}

unsigned short toShort(char* charArray) {
    unsigned short convertedLong = 0;
    unsigned int element;
    for(int i = strlen(charArray) - 1; i >= 0; i--) {
        element = charArray[i];
        convertedLong += element * exponent(256, strlen(charArray) - i - 1);
    }
    return convertedLong;
}