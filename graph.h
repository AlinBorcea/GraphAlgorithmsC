#include <stdio.h>
#include <stdlib.h>

struct Node {
    int id;
    int *vertices;
    int len;
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

/// node funs
struct Node *nodei(int i);
struct Node *before(struct Node *q);

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
    struct Node *p = nodei(a);
    int *nums = (int *) malloc(sizeof(int) * (p->len + 1));
    int i;

    i = 0;
    while (i < p->len && p->vertices[i] < b) {
        nums[i] = p->vertices[i];
        i++;
    }

    /// 1 4 5 6
    /// 1 4 6
    nums[i] = b;

    while (i < p->len) {
        nums[i + 1] = p->vertices[i];
        i++;
    }

    free(p->vertices);
    p->vertices = nums;
    p->len++;
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
    for (struct Node *p = first; p; p = p->next) {
        if (hasId(p, id))
            deleteId(&p, id);        
    }
}

void deleteId(struct Node **p, int id) {
    int *nums = (int *) malloc(sizeof(int) * ((*p)->len - 1));
    int i;
    
    i = 0;
    while ((*p)->vertices[i] != id) {
        nums[i] = (*p)->vertices[i];
        i++;
    }

    while (i < (*p)->len - 1) {
        nums[i] = (*p)->vertices[i + 1];
        i++;
    }

    if (i == 0) {
        free(nums);
        nums = NULL;
    }

    free((*p)->vertices);
    (*p)->vertices = nums;
    (*p)->len--;
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
        if (p->id != id && p->len > 0 && hasId(p, id))
            c++;
    }
    return c;
}

int outRank(int id) {
    struct Node *p = nodei(id);
    return ((p && p->len) ? p->len : -1);
}

int hasId(struct Node *p, int id) {
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

struct Node *nodei(int id) {
    struct Node *p = first;
    while (p && p->id < id)
        p = p->next;

    return ((p && p->id == id) ? p : NULL);
}

struct Node *before(struct Node *q) {
    if (q == first)
        return first;

    struct Node *p = first;
    while (p && p->next != q)
        p = p->next;

    return p;
}
