#include <stdio.h>
#include <stdlib.h>

int main() {
    int isLoggedIn = 1; // Change this value for testing (0 - not logged, 1 - logged)
    int isAdmin = 0;    // Change this value for testing (0 - not admin, 1 - admin)

    if (!isLoggedIn) {
        system("start http://example.com/log");
    } else if (isAdmin) {
        system("start http://example.com/adm");
    } else {
        system("start http://example.com/user");
    }

    return 0;
}