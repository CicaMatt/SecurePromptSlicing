#include <stdlib.h>
    
    void checkLoginStatus(int isLoggedIn, int isAdmin) {
        if (isLoggedIn) {
            if (isAdmin) {
                redirectToAdminPage();
            } else {
                redirectToUserPage();
            }
        } else {
            redirectToLoginPage();
        }
    }