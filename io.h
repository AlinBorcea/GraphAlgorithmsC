#include "graph.h"

void readNodes();
void createGraphFromFile(char *path);

/// printing funs
void printNodes();
void printOneNode(struct Node *p);
void printRanks();
void printNodesInFile(char *path);
void printOneNodeInFile(FILE *file, struct Node *p);

int *neighbors(int n);

struct Node *newNode();

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

struct Node *newNode() {
    struct Node *p = (struct Node *) malloc(sizeof(struct Node));
    printf("id: ");
    scanf("%d", &p->id);
    printf("len: ");
    scanf("%d", &p->len);
    p->vertices = neighbors(p->len);
    p->next = 0;
    return p;
}

// is there a better way to delete contents of a file?
void printNodesInFile(char *path) {
    system("rm out_file.txt");
    system("touch out_file.txt");
    FILE *file = fopen(path, "w");
    for (struct Node *p = first; p; p = p->next) 
        printOneNodeInFile(file, p);

    fclose(file);
}

void printOneNodeInFile(FILE *file, struct Node *p) {
    fprintf(file, "%d -> [", p->id);
    if (!p->vertices) {
        fprintf(file, "none]\n");
    } else {
        fprintf(file, "%d", p->vertices[0]);
        for (int i = 1; i < p->len; i++)
            fprintf(file, ", %d", p->vertices[i]);
        fprintf(file, "]\n");
    }
}

void printNodes() {
    for (struct Node *p = first; p; p = p->next) 
        printOneNode(p);
}

void printOneNode(struct Node *p) {
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
    for (struct Node *p = first; p; p = p->next)
        printf("in rank of %d is %d\n", p->id, inRank(p->id));
}
