#include <string.h>
#include "reader.h"

int main() {
    printf("\e[1;1H\e[2J");
    char option[10];
    int n;
    do {
        printf("option$ ");
        scanf("%s", option);

        if (!strcmp(option, "read")) 
            readNodes();

        else if (!strcmp(option, "print"))
            printNodes();

        else if (!strcmp(option, "file"))
            createGraphFromFile("nums.txt");

        else if (!strcmp(option, "outfile"))
            printNodesInFile("out_file.txt");

        else if (!strcmp(option, "insbefore")) {
            struct Node *p = (struct Node *) malloc(sizeof(struct Node));
            p->id = -1;
            p->len = 1;
            p->vertices = (int *) malloc(sizeof(int));
            p->next = NULL;
            p->vertices[0] = 0;

            insertBefore(p, first->next);

        } else if (!strcmp(option, "insafter")) {
            struct Node *p = (struct Node *) malloc(sizeof(struct Node));
            p->id = 69;
            p->len = 1;
            p->vertices = (int *) malloc(sizeof(int));
            p->next = NULL;
            p->vertices[0] = 1;

            insertAfter(p, first->next->next);

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
