#include <stdio.h>
#include <stdlib.h>

struct Array {
    int val;
    struct Array *next;
};

void insertOrderedVal(struct Array *first, int val);
void deleteVal(struct Array *first, int val);
void printArray(struct Array *first);

struct Array *newVal(int val);

void insertOrderedVal(struct Array *p, int val) {
    if (!p) {
        p = newVal(val);
        return;
    }

    struct Array *q = 0;
    while (p && p->val < val) {
        q = p;
        p = p->next;
    }

    struct Array *newElement = newVal(val);
    if (p && !p->next) {
        p->next = newElement;
        return;
    }

    q->next = newElement;
    newElement->next = p;
}

void deleteVal(struct Array *first, int val) {
    struct Array *p = first;
    if (first->val == val) {
        first = first->next;
        free(p);
        return;
    }

    struct Array *q = 0;
    while (p && p->val != val) {
        q = p;
        p = p->next;
    }

    if (p && !p->next) {
        q->next = 0;
        free(p);
        return;
    }

    if (p) {
        q->next = p->next;
        free(p);
    }
}

void printArray(struct Array *first) {
    for (struct Array *p = first; p; p = p->next)
        printf("%d ", p->val);
    printf("\n");
}

struct Array *newVal(int val) {
    struct Array *p = (struct Array *) malloc(sizeof(struct Array));
    p->val = val;
    p->next = 0;
    return p;
}
