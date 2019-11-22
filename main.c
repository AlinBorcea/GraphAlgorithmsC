#include <string.h>
#include "reader.h"

int main() {
    struct node *h = 0;
    char option[10];
    int id;
    do {
        printf("option$ ");
        scanf("%s", option);

        if (!strcmp(option, "read")) {
            readNodes();
            h = first;
        }
        else if (!strcmp(option, "print"))
            printNodes();
        else if (!strcmp(option, "del")) {
            printf("id .. "); 
            scanf("%d", &id);
            deleteNode(nodeI(id));
            printf("%d", h->id);
        
        } else if (!strcmp(option, "clear"))
            printf("\e[1;1H\e[2J");

        

    } while (strcmp(option, "exit")); 

    printf("\n");
    return 0;
}
