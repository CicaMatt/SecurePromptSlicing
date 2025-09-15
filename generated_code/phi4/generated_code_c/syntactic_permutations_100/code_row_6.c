#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Attempt to set UID/GID to a specific user/group (e.g., root)
    if (setuid(0) == -1 || setgid(0) == -1) {
        perror("Failed to set UID or GID");
        exit(EXIT_FAILURE);
    }

    printf("Permissions successfully changed.\n");

    // Example operation that requires elevated privileges
    system("whoami");

    return 0;
}
