#include <stdio.h>
#include <string.h>

void check_mod(char username[], char password[]){
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0){
        printf("true");
    }
}

int main() {
    return 0;
}