#include <stdio.h>
#include <stdlib.h>

struct Array {
    int val;
    struct Array *next;
};

struct Array *first = 0;
struct Array *last = 0;

void insertOrderedVal(int val);
void deleteVal(int val);
void printArray();

struct Array *newVal(int val);

void insertOrderedVal(int val) {
    if (!first) {
        first = newVal(val);
        last = first;
     
    } else if (last->val < val) {
        struct Array *p = newVal(val);
        last->next = p;
        last = p;

    } else {
        struct Array *newElement = newVal(val);
        struct Array *p = first;
        struct Array *q = 0;
        while (p && p->val < val) {
            q = p;
            p = p->next;
        }

        q->next = newElement;
        newElement->next = p;
    }
}

void deleteVal(int val) {
    struct Array *p = first;
    if (first->val == val) {
        first = first->next;
        free(p);
        return;
    }

    if (last->val == val) {
        while (p->next != last)
            p = p->next;

        free(last);
        last = p;
        last->next = 0;
        return;
    }

    struct Array *q = 0;
    while (p && p->val != val) {
        q = p;
        p = p->next;
    }

    if (p) {
        q->next = p->next;
        free(p);
    }
}

void printArray() {
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
