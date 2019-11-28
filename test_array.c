#include <stdio.h>
#include "array.h"

int main() {
    insertOrderedVal(1);
    insertOrderedVal(3);
    insertOrderedVal(5);
    insertOrderedVal(4);

    deleteVal(3);
    //deleteVal(8);

    printArray();
    printf("\n");
    return 0;
}