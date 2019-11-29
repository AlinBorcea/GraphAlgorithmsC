#include "graph.h"

void createGraphFromFile(char *path);

void printRanks();
void printNodesInFile(char *path);
void printOneNodeInFile(FILE *file, struct Node *p);

struct Node *newNode();
struct Array *newEdges();

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
    if (!p->edges) {
        fprintf(file, "none]\n");
    } else {
        fprintf(file, "%d", p->edges->val);
        for (struct Array *q = p->edges->next; q; q = q->next)
            fprintf(file, ", %d", q->val);
        fprintf(file, "]\n");
    }
}

void printInRanks() {
    for (struct Node *p = first; p; p = p->next)
        printf("in rank of %d is %d\n", p->id, inRank(p->id));
}

struct Node *newNode() {
    struct Node *p = (struct Node*) malloc(sizeof(struct Node));
    printf("id: ");
    scanf("%d", &p->id);
    p->edges = newEdges();
    p->next = 0;
    return p;
}

struct Array *newEdges(int id) {
    struct Array *edges = 0;
    int i, len, x;

    printf("len: ");
    scanf("%d", &len);
    printf("%d -> ", id);
    for (i = 0; i < len; i++) {
        scanf("%d", &x);
        insertOrderedVal(&edges, x);
    }
    return edges;
}
