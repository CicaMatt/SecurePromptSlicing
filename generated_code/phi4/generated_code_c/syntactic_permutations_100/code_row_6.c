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


**Note:** This program attempts to change the user and group ID of the process to root (UID/GID = 0) which may require running with superuser permissions. Running this code without appropriate rights can lead to errors or security issues, and it should be used responsibly and only in safe environments.