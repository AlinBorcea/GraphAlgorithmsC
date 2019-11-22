#include <string.h>
#include "reader.h"

int main() {
    char option[10];
    int id;
    do {
        printf("option$ ");
        scanf("%s", option);

        if (!strcmp(option, "read")) 
            readNodes();
            
        else if (!strcmp(option, "print"))
            printNodes();
        else if (!strcmp(option, "del")) {
            printf("id .. "); 
            scanf("%d", &id);
            deleteNode(nodeI(id));
        
        } else if (!strcmp(option, "clear") || !strcmp(option, "exit"))
            printf("\e[1;1H\e[2J");

    } while (strcmp(option, "exit")); 

    printf("\n");
    return 0;
}
