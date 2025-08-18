#include <stdio.h>
#include <stdlib.h>

char* url = "/ping";

void decorator(char *endpoint, void (*func)(void)) {
    if (strcmp(endpoint, url) == 0) {
        func();
    }
}

void ping() {
    system("ping -c 4 google.com > ping_result.txt");
    FILE *file = fopen("ping_result.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

int main() {
    decorator(url, ping);
    return 0;
}