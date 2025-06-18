#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Check if user is logged in
    if (!isLoggedIn()) {
        printf("You must be logged in to view the page!\n");
        return EXIT_FAILURE;
    }

    // Check if user is admin
    char *username = argv[1];
    int isAdmin = isUserAdmin(username);
    if (isAdmin) {
        printf("You are an admin, redirecting to the admin page...\n");
        execl("/usr/local/bin/admin-page", "admin-page", username, NULL);
    } else {
        printf("Redirecting to the user page...\n");
        execl("/usr/local/bin/user-page", "user-page", username, NULL);
    }

    return EXIT_SUCCESS;
}