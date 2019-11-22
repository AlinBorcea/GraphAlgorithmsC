#include <stdio.h>
#include <stdlib.h>

struct node {
    int id;
    int *vertices;
    int len;
    struct node *next;
};

void addNode(struct node *p);

void deleteNode(struct node *target);
void deleteIdInAll(int id);
void deleteId(struct node **p, int id);

void printNodes();
void printOneNode(struct node *p);
void printRanks();

int inRank(int id);
int outRank(int id);
int hasId(struct node *p, int id);

struct node *nodeI(int i);
struct node *getBefore(struct node *q);

struct node *first = 0;
struct node *last = 0;

void addNode(struct node *p) {
    if (!first) {
        first = p;
        last = first;
    } else {
        last->next = p;
        last = p;
    }
}

void deleteNode(struct node *target) {
    if (target) {
        if (target == first) {
            first = first->next;
    
        } else if (target == last) {
            last = getBefore(last);
            last->next = NULL;
    
        } else {
            getBefore(target)->next = target->next;
        }
        deleteIdInAll(target->id);
        free(target);
    }
}

void deleteIdInAll(int id) {
    for (struct node *p = first; p; p = p->next) {
        if (hasId(p, id))
            deleteId(&p, id);        
    }
}

void deleteId(struct node **p, int id) {
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

void printNodes() {
    for (struct node *p = first; p; p = p->next) 
        printOneNode(p);
}

void printOneNode(struct node *p) {
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
    for (struct node *p = first; p; p = p->next)
        printf("in rank of %d is %d\n", p->id, inRank(p->id));
}

void printOutRanks() {
    int rank;
    for (struct node *p = first; p; p = p->next) {
        rank = outRank(p->id);
        printf("out rank of node %d is ", p->id);
        ((rank) ? printf("%d\n", rank) : printf("none"));
    }
}

int inRank(int id) {
    int c = 0;
    for (struct node *p = first; p; p = p->next) {
        if (p->id != id && p->len > 0 && hasId(p, id))
            c++;
    }
    return c;
}

int outRank(int id) {
    struct node *p = nodeI(id);
    return ((p && p->len) ? p->len : -1);
}

int hasId(struct node *p, int id) {
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

struct node *nodeI(int id) {
    struct node *p = first;
    while (p && p->id < id)
        p = p->next;

    return ((p && p->id == id) ? p : NULL);
}

struct node *getBefore(struct node *q) {
    struct node *p = first;
    while (p && p->next != q)
        p = p->next;

    return p;
}
