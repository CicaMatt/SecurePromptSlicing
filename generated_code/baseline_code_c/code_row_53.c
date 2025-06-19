#include <stdio.h>
#include <stdbool.h>
#include "user_management.h"

int main() {
    User* user = get_current_user();
    if (user == NULL) {
        redirect_to_login();
    } else if (user->is_admin()) {
        redirect_to_admin();
    } else {
        redirect_to_user();
    }
}