#include <stdio.h>

struct node {
    int id;
    int *vertices;
    int len;
    struct node *next;
};

void addNode(struct node *p);
void printNodes();
void printOneNode(struct node *p);
void printRanks();
int inRank(int id);
int hasId(struct node *p, int id);

struct node *first = 0;
struct node *last = 0;

void addNode(struct node *p) {
    if (!first) {
        first = p;
        last = first;
    } else {
        last->next = p;
        last = p;
    }
}

void printNodes() {
    for (struct node *p = first; p; p = p->next) 
        printOneNode(p);
}

void printOneNode(struct node *p) {
    printf("%d -> [", p->id);
    if (!p->vertices) {
        printf("none]\n");
    } else {
        printf("%d", p->vertices[0]);
        for (int i = 1; i < p->len; i++)
            printf(", %d", p->vertices[i]);
        printf("]\n");
    }
}

void printInRanks() {
    for (struct node *p = first; p; p = p->next)
        printf("in rank of %d is %d\n", p->id, inRank(p->id));
}

int inRank(int id) {
    int c = 0;
    for (struct node *p = first; p; p = p->next) {
        if (p->id != id && p->len > 0 && hasId(p, id))
            c++;
    }
    return c;
}

int hasId(struct node *p, int id) {
    int l = 0, r = p->len - 1, m;
    while (l <= r) {
        m = l + (r - 1) / 2;
        if (p->vertices[m] == id)
            return 1;

        if (p->vertices[m] < id)
            l = m + 1;
        else 
            r = m - 1;
    }
    return 0;
}
