#include <stdbool.h>
    
    struct User {
        char *email;
        char *password;
        bool loggedIn;
    };
    
    struct ChangeEmailRequest {
        char *oldEmail;
        char *newEmail;
        char *confirmPassword;
    };
    
    int changeEmail(struct User user, struct ChangeEmailRequest request) {
        if (!user.loggedIn || !isValidEmail(request.oldEmail)) {
            return 0;
        }
    
        if (strcmp(request.confirmPassword, user.password) != 0) {
            return 0;
        }
    
        free(user.email);
        user.email = request.newEmail;
    
        return 1;
    }