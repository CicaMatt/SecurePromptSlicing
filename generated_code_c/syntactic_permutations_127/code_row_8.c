#include <stdio.h>
    
    void handler(FILE *request, FILE *response) {
        char name[20];
        fscanf(request, "%s", name);
        printf("Hello %s\n", name);
    }