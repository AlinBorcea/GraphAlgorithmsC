#include "algorithms.h"

void createGraphFromFile(char *path) {
    FILE *file = fopen(path, "r");
    struct Node *p;
    int i, len, x;
    
    while (!feof(file)) {
        p = (struct Node *) malloc(sizeof(struct Node));
        p->id = -1;
        p->edges = NULL;
        p->next = NULL;

        fscanf(file, "%d", &p->id);
        fscanf(file, "%d", &len);
        for (i = 0; i < len; i++) {
            fscanf(file, "%d", &x);
            insertOrderedVal(&p->edges, x);
        }
        addNode(p);
    }
    fclose(file);
}

int main() {
    createGraphFromFile("nums.txt");
    dfsUtil(first, 2);

    return 0;
}