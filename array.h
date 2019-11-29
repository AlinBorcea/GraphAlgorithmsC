#include <stdio.h>
#include <stdlib.h>

struct Array {
    int val;
    struct Array *pre;
    struct Array *next;
};

void insertOrderedVal(struct Array **p, int val);
void deleteVal(struct Array *first, int val);
void printArray(struct Array *first);

struct Array *newVal(int val);

void insertOrderedVal(struct Array **first, int val) {
    struct Array *newElement = newVal(val);
    struct Array *p = *first;
    struct Array *q = 0;
    if (!*first) {
        *first = newElement;
    
    } else {
        while (p && p->val < val) {
            q = p;
            p = p->next;
        }

        if (!p) {
            p = newElement;
            newElement->pre = q;
            q->next = p;
        
        } else {
            newElement->next = p;
            newElement->pre = q;
            q->next = newElement;
        }

    }
}

void deleteVal(struct Array *first, int val) {
    struct Array *p = first;
    if (first->val == val) {
        first = first->next;
        free(p);
        return;
    }

    while (p && p->val != val) 
        p = p->next;

    if (p && !p->next) {
        p->pre->next = 0;
        free(p);
        return;
    }

    if (p) {
        p->pre->next = p->next;
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
    p->pre = p->next = 0;
    return p;
}
