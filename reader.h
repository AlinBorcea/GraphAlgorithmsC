#include "graph.h"

void readNodes();
int *neighbors(int n);

void readNodes() {
    int n;
    printf("vertex len .. ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        struct node *p = (struct node*) malloc(sizeof(struct node));
        int m;

        printf("node %d len .. ", i);
        scanf("%d", &m);
        if (m > 0)
        printf("%d -> ", i);

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
    for (int i = 0; i < n; i++) 
        scanf("%d", nums + i);

    return nums;
}