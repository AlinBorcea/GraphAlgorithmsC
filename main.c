#include <string.h>
#include "io.h"

int main() {
    printf("\e[1;1H\e[2J");
    struct Node *first = 0;
    struct Node *last = 0;
    char option[10];
    int n, m;
    
    do {
        printf("option$ ");
        scanf("%s", option);

        if (!strcmp(option, "file"))
            createGraphFromFile("example.txt");

        else if (!strcmp(option, "outfile"))
            printNodesInFile("out_file.txt");

        else if (!strcmp(option, "insbefore")) {
            printf("insert before node.. ");
            scanf("%d", &n);
            insertBefore(newNode(), nodei(n));

        } else if (!strcmp(option, "insafter")) {
            printf("insert before node.. ");
            scanf("%d", &n);
            insertAfter(newNode(), nodei(n));

        } else if (!strcmp(option, "insedge")) {
            printf("a = ");
            scanf("%d", &n);
            printf("b = ");
            scanf("%d", &m);
            insertEdge(n, m);

        } else if (!strcmp(option, "del")) {
            printf("id .. "); 
            scanf("%d", &n);
            deleteNode(nodei(n));
        
        } else if (!strcmp(option, "clear"))
            printf("\e[1;1H\e[2J");

        else if (!strcmp(option, "dfs")) {
            dfsUtil(2);
            printf("\n");
        }

        else if (!strcmp(option, "bfs"))
            bfs(nodei(1));


    } while (strcmp(option, "exit")); 

    printf("\e[1;1H\e[2J");
    return 0;
}
