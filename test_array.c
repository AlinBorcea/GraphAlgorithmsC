#include <stdio.h>
#include "array.h"

int main() {
    int n = 10;
    int *arr = (int *) malloc(sizeof(int) * n);
    int i;

    for (i = 0; i < n; i++)
        arr[i] = i;

    insertOrdered(&arr, &n, 30);
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n\n");
    deleteVal(&arr, &n, 3);
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
    return 0;
}