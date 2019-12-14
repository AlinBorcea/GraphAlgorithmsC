#include <stdio.h>
#include <stdlib.h>
#include "array.h"

struct Node {
    int id;
    struct Array *edges;
    struct Array *costs;
    struct Node *next;
};

/// creation funs
struct Node *graphFromFile(char *path);
void addNode(struct Node **first, struct Node **last, struct Node *p);
void insertBefore(struct Node *first, struct Node *newNode, struct Node *p);
void insertAfter(struct Node *newNode, struct Node *p);
void insertEdge(struct Node *first, int a, int b);

/// deletion funs
void deleteNode(struct Node *first, struct Node *last, struct Node *target);
void deleteIdInAll(struct Node *first, int id);
void deleteId(struct Node **p, int id);

/// int funs
int inRank(struct Node *first,  int id);
int outRank(struct Node *first, int id);
int hasId(struct Node *p, int id);
int nodeLen(struct Node *first);

/// node funs
struct Node *nodei(struct Node *first, int i);
struct Node *before(struct Node *first, struct Node *q);
struct Node *last(struct Node *first);

/// algorithms
void dfs(struct Node *first, struct Node *p, int *visited);
void dfsUtil(struct Node *first, int start);
void dijkstra(struct Node *first, int start);

/// "constructor"
struct Node *graphFromFile(char *path) {
    FILE *file = fopen(path, "r");
    struct Node *first = 0;
    struct Node *last = 0;
    struct Node *p;
    int i, len, x;
    
    while (!feof(file)) {
        p = (struct Node *) malloc(sizeof(struct Node));
        p->id = -1;
        p->edges = p->costs = NULL;
        p->next = NULL;

        fscanf(file, "%d", &p->id);
        fscanf(file, "%d", &len);
        for (i = 0; i < len; i++) {
            fscanf(file, "%d", &x);
            insertOrderedVal(&p->edges, x);
        }
        addNode(&first, &last, p);
    }
    fclose(file);
    return first;
}

void addNode(struct Node **first, struct Node **last, struct Node *p) {
    if (!*first) {
        *first = p;
        *last = first;
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
