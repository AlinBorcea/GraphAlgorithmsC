#include <stdio.h>
#include <stdlib.h>
#include "array.h"

struct Node {
    int id;
    struct Array *edges;
    struct Node *next;
};

struct Node *first = 0;
struct Node *last = 0;

/// creation funs
void addNode(struct Node *p);
void insertBefore(struct Node *newNode, struct Node *p);
void insertAfter(struct Node *newNode, struct Node *p);
void insertEdge(int a, int b);

/// deletion funs
void deleteNode(struct Node *target);
void deleteIdInAll(int id);
void deleteId(struct Node **p, int id);

/// int funs
int inRank(int id);
int outRank(int id);
int hasId(struct Node *p, int id);
int nodeLen(struct Node *first);

/// node funs
struct Node *nodei(int i);
struct Node *before(struct Node *q);

/// algorithms
void dfs(struct Node *p, int *visited);
void dfsUtil(int start);


void addNode(struct Node *p) {
    if (!first) {
        first = p;
        last = first;
    } else {
        last->next = p;
        last = p;
    }
}

void insertBefore(struct Node *newNode, struct Node *p) {
    newNode->next = p;
    before(p)->next = newNode;
}

void insertAfter(struct Node *newNode, struct Node *p) {
    newNode->next = p->next;
    p->next = newNode;
}

void insertEdge(int a, int b) {
    insertOrderedVal(&nodei(a)->edges, b);
}

void deleteNode(struct Node *target) {
    if (target) {
        if (target == first) {
            first = first->next;
    
        } else if (target == last) {
            last = before(last);
            last->next = NULL;
    
        } else {
            before(target)->next = target->next;
        }
        deleteIdInAll(target->id);
        free(target);
    }
}

void deleteIdInAll(int id) {
    for (struct Node *p = first; p; p = p->next) 
        deleteVal(&p->edges, id);
}

void printOutRanks() {
    int rank;
    for (struct Node *p = first; p; p = p->next) {
        rank = outRank(p->id);
        printf("out rank of node %d is ", p->id);
        ((rank) ? printf("%d\n", rank) : printf("none"));
    }
}

int inRank(int id) {
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

int outRank(int id) {
    int c = 0;
    for (struct Array *p = nodei(id)->edges; p; p = p->next)
        c++;
    return c;
}

int nodeLen(struct Node *first) {
    int c = 0;
    for (struct Node *p = first; p; p = p->next)
        c++;
    return c;
}

struct Node *nodei(int id) {
    struct Node *p = first;
    while (p && p->id < id)
        p = p->next;

    return ((p && p->id == id) ? p : first);
}

struct Node *before(struct Node *q) {
    if (q == first)
        return first;

    struct Node *p = first;
    while (p && p->next != q)
        p = p->next;

    return p;
}

void dfsUtil(int start) {
    int len = nodeLen(first);
    int *visited = (int *) malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
        visited[i] = 0;

    dfs(nodei(start), visited);
}

void dfs(struct Node *p, int *visited) {
    printf("%d ", p->id);
    visited[p->id] = 1;
    for (struct Array *arr = p->edges; arr; arr = arr->next) {
        if (!visited[arr->val])
            dfs(nodei(arr->val), visited);
    }
}

void bfs(struct Node *p) {
    int len = nodeLen(first);
    int *visited = (int *) malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
        visited[i] = 0;

    struct Array *queue = newVal(p->id);
    int lastId;
    while (arrayLen(queue)) {
        printf("%d ", queue->val);
        lastId = queue->val;
        visited[lastId] = 1;
        deleteVal(&queue, queue->val);
        for (struct Array *q = nodei(lastId)->edges; q; q = q->next) {
            if (!visited[q->val]) {
                visited[q->val] = 1;
                insertVal(&queue, q->val);
            }
        }
    }
    printArray(queue);
}
