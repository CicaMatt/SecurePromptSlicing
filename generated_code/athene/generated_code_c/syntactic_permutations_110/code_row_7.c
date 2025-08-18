#include <stdio.h>
#include <stdlib.h>

int get_user_id_status(const char *username) {
    char command[100];
    snprintf(command, sizeof(command), "id %s", username);
    return system(command);
}

int main() {
    const char *username = "testuser";
    int status = get_user_id_status(username);
    printf("Exit status: %d\n", status >> 8);
    return 0;
}