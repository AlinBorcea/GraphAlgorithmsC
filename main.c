#include <string.h>
#include "reader.h"

int main() {
    char option[10];
    do {
        scanf("%s", option);

        if (!strcmp(option, "read"))
            readNodes();
        else if (!strcmp(option, "print"))
            printNodes();

    } while (strcmp(option, "exit")); 

    printf("\n");
    return 0;
}
