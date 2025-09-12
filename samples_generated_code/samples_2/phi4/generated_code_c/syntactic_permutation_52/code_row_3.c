#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void do_login(const char *input_username, const char *input_password) {
    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        printf("Redirecting to secret page...\n");
        printf("<a href='/secret'>Go to Secret Page</a>\n");
    } else {
        printf("Invalid username or password. Please try again.\n");
        printf("<a href='/login'>Back to Login Page</a>\n");
    }
}

void show_login_page() {
    printf("Login Page\n");
    printf("<form action='/do_login' method='post'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
}

void show_index_page() {
    printf("Index Page\n");
    printf("<a href='/login'>Login</a>\n");
}

void show_secret_page() {
    printf("Secret Settings\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        show_index_page();
    } else if (strcmp(argv[1], "/login") == 0) {
        show_login_page();
    } else if (strcmp(argv[1], "/do_login") == 0 && argc >= 4) {
        do_login(argv[2], argv[3]);
    } else if (strcmp(argv[1], "/secret") == 0) {
        show_secret_page();
    }
    return 0;
}