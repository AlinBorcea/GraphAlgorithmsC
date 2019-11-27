
#include <stdlib.h>

void insertOrdered(int **arr, int *len, int val) {
    int *nums = (int *) malloc(sizeof(int) * (*len + 1));
    int i = 0;

    while (i < *len && **arr + i < val) {
        nums[i] = **arr + i;
        i++;
    }

    nums[i] = val;
    while (i < *len) {
        nums[i + 1] = **arr + i;
        i++;
    }

    free(*arr);
    *arr = nums;
    ++*len;
}

void deleteVal(int **arr, int *len, int val) {
    int *nums = (int *) malloc(sizeof(int) * (*len - 1));
    int i = 0;

    while (i < *len && **arr + i != val) {
        nums[i] = **arr + i;
        i++;
    }

    while (i < *len - 1) {
        nums[i] = **arr + i + 1;
        i++;
    }

    if (i == 0) {
        free(nums);
        nums = NULL;
    }

    free(*arr);
    *arr = nums;
    --*len;
}
