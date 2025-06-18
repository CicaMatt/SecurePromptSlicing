#include <stdio.h>
    #include <stdbool.h>
    #include <string.h>

    char *username = "";

    bool do_login(char *user, char *pass) {
        if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    void login_page() {
        printf("Username: ");
        scanf("%s", &username);
        printf("Password: ");
        scanf("%s", &password);
        do_login(username, password);
        if (do_login(username, password)) {
            redirect("secret.html");
        }
        else {
            redirect("index.html");
        }
    }

    void index_page() {
        printf("<a href=\"%s\">Login</a>", "login.html");
    }

    void secret_page() {
        printf("Secret settings");
    }