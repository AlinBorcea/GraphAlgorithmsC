#include <string.h>
#include "io.h"

int main() {
    printf("\e[1;1H\e[2J");
    system("rm history.txt");
    system("touch history.txt");

    FILE *history = fopen("history.txt", "w");
    char option[10];
    int n, m;
    do {
        printf("option$ ");
        scanf("%s", option);
        fprintf(history, "%s\n", option);

        if (!strcmp(option, "read")) 
            readNodes();

        else if (!strcmp(option, "print"))
            printNodes();

        else if (!strcmp(option, "file"))
            createGraphFromFile("nums.txt");

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

    } while (strcmp(option, "exit")); 

    printf("\e[1;1H\e[2J");
    return 0;
}
