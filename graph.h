#include "array.h"

struct Node {
    int id;
    struct Array *edges;
    struct Array *costs;
    struct Node *next;
};

/// creations
struct Node *graphFromFile(char *path, int random);
struct Node *newNode(int id);
void addNode(struct Node **first, struct Node **last, struct Node *p);

/// insertions
void insertBefore(struct Node *first, struct Node *newNode, struct Node *p);
void insertAfter(struct Node *newNode, struct Node *p);
void insertEdge(struct Node *first, int a, int b);

/// deletions
void deleteNode(struct Node *first, struct Node *last, struct Node *target);
void deleteIdInAll(struct Node *first, int id);
void deleteId(struct Node **p, int id);

/// ints
int inRank(struct Node *first,  int id);
int outRank(struct Node *first, int id);
int hasId(struct Node *p, int id);
int nodeLen(struct Node *first);

/// nodes
struct Node *nodei(struct Node *first, int i);
struct Node *before(struct Node *first, struct Node *q);
struct Node *last(struct Node *first);

/// printers
void printGraph(struct Node *first);

/// algorithms
void dfs(struct Node *first, struct Node *p, int *visited);
void dfsUtil(struct Node *first, int start);
void dijkstra(struct Node *first, int start);

/// "constructor"
struct Node *graphFromFile(char *path, int random) {
    FILE *file = fopen(path, "r");
    struct Node *first = 0;
    struct Node *last = 0;
    struct Node *p = 0;
    int len, a, b, c;

    fscanf(file, "%d", &len);
    for (int i = 0; i < len; i++)
        addNode(&first, &last, newNode(i));

    if (random) {
        int it = len;
        while (it) {
            a = rand() % len;
            c = rand() % 100;
            p = nodei(first, a);
            while (c) {
                b = rand() % len;
                insertOrderedVal(&p->edges, b);
                c--;
            }
            it--;
            printf("%d\n", it);
        }

    } else {
        while (!feof(file)) {
            fscanf(file, "%d", &a);
            fscanf(file, "%d", &b);
            insertOrderedVal(&nodei(first, a)->edges, b);
        }
    }
    fclose(file);
    return first;
}

struct Node *newNode(int id) {
    struct Node *p = (struct Node *) malloc(sizeof(struct Node));
    p->id = id;
    p->edges = p->costs = 0;
    p->next = 0;
    return p;
}

void addNode(struct Node **first, struct Node **last, struct Node *p) {
    if (!*first) {
        *first = p;
        *last = *first;
    } else {
        (*last)->next = p;
        *last = p;
    }
}

void insertBefore(struct Node *first, struct Node *newNode, struct Node *p) {
    newNode->next = p;
    before(first, p)->next = newNode;
}

void insertAfter(struct Node *newNode, struct Node *p) {
    newNode->next = p->next;
    p->next = newNode;
}

void insertEdge(struct Node *first, int a, int b) {
    insertOrderedVal(&nodei(first, a)->edges, b);
}

void deleteNode(struct Node *first, struct Node *last, struct Node *target) {
    if (target) {
        if (target == first) {
            first = first->next;
    
        } else if (target == last) {
            last = before(first, last);
            last->next = NULL;
    
        } else {
            before(first, target)->next = target->next;
        }
        deleteIdInAll(first, target->id);
        free(target);
    }
}

void deleteIdInAll(struct Node *first, int id) {
    for (struct Node *p = first; p; p = p->next) 
        deleteVal(&p->edges, id);
}

void printOutRanks(struct Node *first) {
    int rank;
    for (struct Node *p = first; p; p = p->next) {
        rank = outRank(first, p->id);
        printf("out rank of node %d is ", p->id);
        ((rank) ? printf("%d\n", rank) : printf("none"));
    }
}

int inRank(struct Node *first, int id) {
    int c = 0;
    for (struct Node *p = first; p; p = p->next) {
        if (p->id != id) {
            for (struct Array *q = p->edges; q; q = q->next) {
                if (q->val == id) {
                    c++;
                    break;
                }
                if (q->val > id)
                    break;
            }
        }
    }
    return c;
}

int outRank(struct Node *first, int id) {
    int c = 0;
    for (struct Array *p = nodei(first, id)->edges; p; p = p->next)
        c++;
    return c;
}

int nodeLen(struct Node *first) {
    int c = 0;
    for (struct Node *p = first; p; p = p->next)
        c++;
    return c;
}

struct Node *nodei(struct Node *first, int id) {
    struct Node *p = first;
    while (p && p->id < id)
        p = p->next;

    return ((p && p->id == id) ? p : first);
}

struct Node *before(struct Node *first, struct Node *q) {
    if (q == first)
        return first;

    struct Node *p = first;
    while (p && p->next != q)
        p = p->next;

    return p;
}

struct Node *last(struct Node *first) {
    while (first && first->next)
        first = first->next;
    return first;
}

void printGraph(struct Node *first) {
    FILE *file = fopen("out.txt", "w");
    while (first) {
        fprintf(file, "%d -> ", first->id);
        ((first->edges) ? printArrayInFile(file, first->edges) : fprintf(file, "none\n"));
        first = first->next;
    }
}

void dfsUtil(struct Node *first, int start) {
    int len = nodeLen(first);
    int *visited = (int *) malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
        visited[i] = 0;

    dfs(first, nodei(first, start), visited);
}

void dfs(struct Node *first, struct Node *p, int *visited) {
    printf("%d ", p->id);
    visited[p->id] = 1;
    for (struct Array *arr = p->edges; arr; arr = arr->next) {
        if (!visited[arr->val])
            dfs(first, nodei(first, arr->val), visited);
    }
}

void bfs(struct Node *first, struct Node *p) {
    int len = nodeLen(first);
    int *visited = (int *) malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
        visited[i] = 0;

    struct Array *queue = newVal(p->id);
    struct Array *q;
    int qlen = 1;
    while (qlen) {
        printf("%d ", queue->val);
        q = nodei(first, queue->val)->edges;
        visited[queue->val] = 1;
        deleteVal(&queue, queue->val);
        qlen--;
        while (q) {
            if (!visited[q->val]) {
                visited[q->val] = 1;
                insertVal(&queue, q->val);
                qlen++;
            }
            q = q->next;
        }
    }
    printArray(queue);
}

void dijkstra(struct Node *first, int start) {}
