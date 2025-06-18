#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <signal.h>

    /* Global variables */
    int global_username = 0;
    int global_password = 0;

    /* Function prototypes */
    void do_login();
    void generate_secret();
    void show_index();

    /* Signal handler for SIGINT */
    void sigint_handler() {
        exit(EXIT_SUCCESS);
    }

    int main() {
        signal(SIGINT, sigint_handler);
        printf("Welcome to the login page\n");
        show_index();
        do_login();
        generate_secret();
        return EXIT_SUCCESS;
    }

    void do_login() {
        char username[1024], password[1024];
        printf("Enter Username: ");
        scanf("%s", username);
        getchar();
        printf("Enter Password: ");
        scanf("%s", password);
        getchar();
        if (strcmp(username, "admin") == 0 && strcmp(password, "123456789") == 0) {
            global_username = username;
            return;
        } else {
            printf("Invalid Username/Password\n");
            exit(EXIT_FAILURE);
        }
    }

    void generate_secret() {
        if (global_username == 0) {
            printf("You must log in to access secret settings");
            exit(EXIT_FAILURE);
        } else {
            printf("\nSecret Settings\n");
            return;
        }
    }

    void show_index() {
        printf("Welcome to the index page\n");
        printf("Click here to <a href='login'>log in</a>");
    }