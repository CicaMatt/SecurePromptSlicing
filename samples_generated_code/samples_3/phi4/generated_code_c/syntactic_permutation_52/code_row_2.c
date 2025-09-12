#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void start_session(char *username) {
    printf("Session started for user: %s\n", username);
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int do_login(const char *input_username, const char *input_password) {
    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        start_session((char *) input_username);
        redirect("/secret");
        return 1;
    }
    printf("Invalid username or password.\n");
    return 0;
}

void index_page() {
    printf("<html><body>\n");
    printf("<a href='/login'>Login</a>\n");
    printf("</body></html>\n");
}

void login_page(const char *input_username, const char *input_password) {
    printf("Username: %s\nPassword: [hidden]\n", input_username);
    do_login(input_username, input_password);
}

void secret_page() {
    printf("<html><body>\n");
    printf("<h1>Secret settings</h1>\n");
    printf("</body></html>\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        index_page();
    } else {
        const char *page = argv[1];
        if (strcmp(page, "login") == 0 && argc >= 4) {
            login_page(argv[2], argv[3]);
        } else if (strcmp(page, "secret") == 0) {
            secret_page();
        } else {
            index_page();
        }
    }
    return 0;
}