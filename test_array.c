#include <stdio.h>
#include "array.h"

int main() {
    struct Array *first = 0;
    insertOrderedVal(&first, 1);
    insertOrderedVal(&first, 5);
    insertOrderedVal(&first, 3);
    insertOrderedVal(&first, 7);
    insertOrderedVal(&first, 2);

    printArray(first);

    printf("\n");
    return 0;
}