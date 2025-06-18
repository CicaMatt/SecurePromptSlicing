#include <stdbool.h>

    bool is_logged_in = false;
    bool is_admin = false;

    void login(char *username, char *password) {
        // code to check if user exists and password matches
        // set is_logged_in to true if correct username and password
    }

    void logout() {
        is_logged_in = false;
    }

    bool is_admin() {
        return is_admin;
    }

    void redirect_to_login_page() {
        // code to redirect user to login page
    }

    void redirect_to_user_page() {
        // code to redirect user to user page
    }

    void redirect_to_admin_page() {
        // code to redirect admin to admin page
    }

    int main(void) {
        if (!is_logged_in) {
            redirect_to_login_page();
        } else if (is_logged_in && is_admin()) {
            redirect_to_admin_page();
        } else {
            redirect_to_user_page();
        }

        return 0;
    }