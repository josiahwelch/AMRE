// Josiah Welch
// Arca M
// 11/23/24
#include <stdio.h>
#include "interpreter.h"

int main()
{
    char helloWorld[16] = "Hello Worl";
    append(helloWorld, 'd');
    printf(helloWorld);
    return 0;
}