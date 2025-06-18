#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
// #define ADMIN 0 // set to 1 if the user is an admin

char *user_page() {
    char *html = "<html><body>User Page</body></html>";
    return html;
}

char *admin_page() {
    char *html = "<html><body>Admin Page</body></html>";
    return html;
}

char *login_page() {
    char *html = "<html><body>Login Page</body></html>";
    return html;
}

int main(void) {
    // check if the user is logged in
#ifdef ADMIN
    printf("%s", admin_page());
#else
    printf("%s", user_page());
#endif
    return 0;
}