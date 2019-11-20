#include <iostream>
#include "graph.h"

using namespace std;

void readNodes(int n);
int *neighbors(int n);

int main() {
    int n;
    cout << "number of vertices.. "; cin >> n;
    readNodes(n);
    printNodes();
    printInRanks();

    cout << endl;
    return 0;
}

void readNodes(int n) {
    for (int i = 0; i < n; i++) {
        node *p = new node;
        int m;

        cout << "number of neighbors for node " << i << " .. "; cin >> m;
        p->id = i;
        p->vertices = neighbors(m);
        p->len = m;
        p->next = 0;
        addNode(p);
    }
}

int *neighbors(int n) {
    if (n < 1) 
        return NULL;
    
    int *nums = new int[n];
    for (int i = 0; i < n; i++) {
        cout << "neighbor " << i << " .. "; 
        cin >> nums[i];
    }
    return nums;
}
