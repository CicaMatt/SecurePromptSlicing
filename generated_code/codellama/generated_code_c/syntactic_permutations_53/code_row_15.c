#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Check if user is logged in
    if (!is_logged_in()) {
        redirect_to_login();
    } else {
        // Check if user is admin
        if (is_admin()) {
            redirect_to_admin();
        } else {
            redirect_to_user();
        }
    }
}