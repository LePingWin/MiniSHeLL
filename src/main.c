#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include "tools.h"

int main(int argc, char* argv[])
{
    node test;
    test.value = "2";

    printf("%s\n",test.value);
    return EXIT_SUCCESS;
}