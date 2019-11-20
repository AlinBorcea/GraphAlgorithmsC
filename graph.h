#include <iostream>

using namespace std;

struct node {
    int id;
    int *vertices;
    int len;
    node *next;
};

void addNode(node *p);
void printNodes();
void printOneNode(node *p);
void printRanks();
int inRank(int id);
bool hasId(node *p, int id);

node *first = 0;
node *last = 0;

void addNode(node *p) {
    if (!first) {
        first = p;
        last = first;
    } else {
        last->next = p;
        last = p;
    }
}

void printNodes() {
    for (node *p = first; p; p = p->next) 
        printOneNode(p);
}

void printOneNode(node *p) {
    cout << p->id << " -> [";
    if (!p->vertices) {
        cout << "none]\n";
    } else {
        cout << p->vertices[0];
        for (int i = 1; i < p->len; i++)
            cout << ", " << p->vertices[i];
        cout << "]\n";
    }
}

void printInRanks() {
    for (node *p = first; p; p = p->next) 
        cout << "in rank of " << p->id << " is " << inRank(p->id) << endl;
}

int inRank(int id) {
    int c = 0;
    for (node *p = first; p; p = p->next) {
        if (p->id != id && p->len > 0 && hasId(p, id))
            c++;
    }
    return c;
}

bool hasId(node *p, int id) {
    int l = 0, r = p->len - 1, m;
    while (l <= r) {
        m = l + (r - 1) / 2;
        if (p->vertices[m] == id)
            return true;

        if (p->vertices[m] < id)
            l = m + 1;
        else 
            r = m - 1;
    }

    return false;
}
