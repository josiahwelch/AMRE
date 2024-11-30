#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "jwlib.h"

enum ByteIndicator
{
    INSTRUCTION,
    FIRST_ARGUMENT_LENGTH,
    SECOND_ARGUMENT_LENGTH,
    FIRST_ARGUMENT_TYPE,
    SECOND_ARGUMENT_TYPE,
    FIRST_ARGUMENT,
    SECOND_ARGUMENT,
    JUMP_LABEL_LENGTH,
    JUMP_LABEL
};

enum Instruction
{
    MOV,
    ADD,
    SUB,
    MUL,
    DIV, // arithmetic
    INC,
    DEC,
    IFJ,
    JMP,
    GTJ
};

enum Warning
{
    VERSION_WARNING,
    LARGE_ALLOC,
    UNNECCESSARY_ARG
};

enum Error
{
    VERSION_ERROR,
    UNRECOGNIZED_INSTRUCTION
};

void warning(char *warning, enum Warning warningType)
{
    char warningMessage[64] = "::WARNING[";
    switch (warningType)
    {
    case VERSION_WARNING:
        strcat(warningMessage, "mismatched version warning]: ");
        break;
    case LARGE_ALLOC:
        strcat(warningMessage, "large memory allocaton warning]: ");
        break;
    default:
        strcat(warningMessage, "miscellaneous warning]: ");
        break;
    }
    strcat(warningMessage, warning);
    fprintf(stderr, warningMessage);
}

void error(char *error, enum Error errorType)
{
    char errorMessage[64] = "::ERROR[";
    switch (errorType)
    {
    case VERSION_ERROR:
        strcat(errorMessage, "incorrect version error]: ");
        break;
    case UNRECOGNIZED_INSTRUCTION:
        strcat(errorMessage, "instruction not found error]: ");
        break;
    default:
        strcat(errorMessage, "miscellaneous error]: ");
        break;
    }
    strcat(errorMessage, error);
    fprintf(stderr, errorMessage);
}

int interpreter(char *bytecode, int suppressWarnings)
{

    enum Error errorBuffer; // to store the error type so it can be passed as argument two of error()

    const short majorVersion = 0;
    const short minorVersion = 1;
    const short patchVersion = 0;

    char majorVersionCode[] = {bytecode[6], bytecode[7]};
    char minorVersionCode[] = {bytecode[8], bytecode[9]};
    char patchVersionCode[] = {bytecode[10], bytecode[11]};

    short programMajorVersion = toLong(majorVersionCode);
    short programMinorVersion = toLong(minorVersionCode);
    short programPatchVersion = toLong(patchVersionCode);

    enum ByteIndicator byteIndicator = INSTRUCTION;

    enum Instruction Instruction;

    if (bytecode[0] != 222 || bytecode[1] != 173 || bytecode[2] != 190 || bytecode[3] != 239 || bytecode[4] != 250 || bytecode[5] != 206) 
    {
        return 1;
    }

    if (programMajorVersion != majorVersion)
    {
        return 2;
    }

    if ((programMinorVersion != minorVersion || programPatchVersion != patchVersion) && !suppressWarnings)
    {
        enum Warning versionWarning = VERSION_WARNING;
        char buffer[16];
        char warningMessage[64] = "AIB program version(";
        strcat(warningMessage, longToString(programMajorVersion, buffer));
        strcat(warningMessage, ".");
        strcat(warningMessage, longToString(programMinorVersion, buffer));
        strcat(warningMessage, ".");
        strcat(warningMessage, longToString(programPatchVersion, buffer));
        strcat(warningMessage, ") isn't supported by this AMRE version.");
        warning(warningMessage, versionWarning);
    }

    char memorySize[6] = {bytecode[10], bytecode[11], bytecode[12], bytecode[13], bytecode[14], bytecode[15]}; // initializes memory allocated from program specification
    unsigned char *pointer = (unsigned char *)malloc(toLong(memorySize));

    int index = 16;

    char jumpLabels[16][16];
    int jumpIndices[16];

    unsigned short firstArgumentLength;
    unsigned short secondArgumentLength;
    unsigned short jumpLabelLength;

    unsigned short firstArgumentType;
    unsigned short secondArgumentType;

    char jumpLabel[16];
    char firstArgument[64];
    char secondArgument[64];

    while (index < strlen(bytecode))
    { // primary computational loop

        switch (byteIndicator)
        {

        case INSTRUCTION:

            switch (bytecode[index])
            {
            case 0:
                Instruction = MOV;
                byteIndicator = FIRST_ARGUMENT_LENGTH; // sets the byteIndicator to the next position
                break;
            case 1:
                Instruction = ADD;
                byteIndicator = FIRST_ARGUMENT_LENGTH;
                break;
            case 2:
                Instruction = SUB;
                byteIndicator = FIRST_ARGUMENT_LENGTH;
                break;
            case 3:
                Instruction = MUL;
                byteIndicator = FIRST_ARGUMENT_LENGTH;
                break;
            case 4:
                Instruction = DIV;
                byteIndicator = FIRST_ARGUMENT_LENGTH;
                break;
            case 5:
                Instruction = INC;
                byteIndicator = FIRST_ARGUMENT_LENGTH;
                break;
            case 6:
                Instruction = DEC;
                byteIndicator = FIRST_ARGUMENT_LENGTH;
                break;
            case 7:
                Instruction = IFJ;
                byteIndicator = JUMP_LABEL_LENGTH;
                break;
            case 8:
                Instruction = JMP;
                byteIndicator = JUMP_LABEL_LENGTH;
                break;
            case 9:
                Instruction = GTJ;
                byteIndicator = JUMP_LABEL_LENGTH;
                break;
            default:
                errorBuffer = UNRECOGNIZED_INSTRUCTION;
                error("Unable to parse valid instruction.", errorBuffer);
                return 2;
                break;
            }
            index++; // sets the index to the next byte
            break;
        case FIRST_ARGUMENT:
            for (int i = 0; i < firstArgumentLength; i++)
            {
                append(firstArgument, bytecode[index]);
            }
            if (firstArgumentType != 0 && Instruction == INC)
            {
            }
        case FIRST_ARGUMENT_TYPE:
            firstArgumentType = bytecode[index];
            byteIndicator = FIRST_ARGUMENT;
            index++;
            break;
        case FIRST_ARGUMENT_LENGTH:
            firstArgumentLength = bytecode[index];
            byteIndicator = FIRST_ARGUMENT_TYPE;
            index++;
            break;
            // case
        }
    }
    return 0;
}