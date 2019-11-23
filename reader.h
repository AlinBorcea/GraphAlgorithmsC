#include "graph.h"

void readNodes();
void createGraphFromFile(char *path);

int *neighbors(int n);

void readNodes() {
    int n;
    printf("vertex len .. ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        struct Node *p = (struct Node*) malloc(sizeof(struct Node));
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

void createGraphFromFile(char *path) {
    FILE *file = fopen(path, "r");
    struct Node *p;
    
    int i;
    while (!feof(file)) {
        p = (struct Node *) malloc(sizeof(struct Node));
        p->id = -1;
        p->vertices = NULL;
        p->len = 0;
        p->next = NULL;

        fscanf(file, "%d", &p->id);
        fscanf(file, "%d", &p->len);

        p->vertices = (int *) malloc(sizeof(int) * p->len);
        for (i = 0; i < p->len && !feof(file); i++)
            fscanf(file, "%d", p->vertices + i);

        addNode(p);
    }
    fclose(file);
}

int *neighbors(int n) {
    if (n < 1) 
        return NULL;
    
    int *nums = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) 
        scanf("%d", nums + i);

    return nums;
}