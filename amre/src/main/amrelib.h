#include <stdio.h>

void mov(unsigned char* memory, unsigned int pointer, unsigned char* value, int type) {

    int parseLength;

    switch(type) {
        case 1:
        case 2:
            parseLength = 1;
            break;
        case 3:
        case 4:
            parseLength = 2;
            break;
        case 5:
        case 6:
        case 7:
            parseLength = 4;
            break;
        case 8:
        case 9:
            parseLength = 8;
            break;
        case 10:
            parseLength = 16;
            break;
        case 11:
            
    }

}