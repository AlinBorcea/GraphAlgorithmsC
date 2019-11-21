#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void readNodes(int n);
int *neighbors(int n);

int main() {
    int n;
    printf("number of vertices.. ");
    scanf("%d", &n);

    readNodes(n);
    printNodes();
    printInRanks();

    printf("\n");
    return 0;
}

void readNodes(int n) {
    for (int i = 0; i < n; i++) {
        struct node *p = (struct node*) malloc(sizeof(struct node));
        int m;

        printf("number of neighbors for node %d .. ", i);
        scanf("%d", &m);

        p->id = i;
        p->vertices = neighbors(m);
        p->len = m;
        p->next = 0;
        addNode(p);
    }
}

int *neighbors(int n) {
    if (n < 1) 
        return NULL;
    
    int *nums = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        printf("neighbor %d ", i);
        scanf("%d", nums + i);
    }
    return nums;
}
