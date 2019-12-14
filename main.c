#include "graph.h"

int main() {
    printf("\e[1;1H\e[2J");
    char file[] = "example.txt";
    struct Node *graph = graphFromFile(file, 1);
    printGraph(graph);

    printf("\n");
    return 0;
}
