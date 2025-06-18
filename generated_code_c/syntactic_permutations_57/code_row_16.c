#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <shadow.h>

int main() {
    // Asks user for old email
    char* old_email = getpass("Old Email: ");
    
    // Asks user for new email
    char* new_email = getpass("New Email: ");
    
    // Asks user for confirm password
    char* confirm_password = getpass("Confirm Password: ");
    
    // Gets the shadow file entry for the user's old email
    struct spwd *sp = getspnam(old_email);
    
    if (sp == NULL) {
        printf("User does not exist\n");
        return 1;
    }
    
    // Verifies that the provided confirm password matches the shadow file entry
    char* encrypted_password = crypt(confirm_password, sp->sp_pwdp);
    if (strcmp(encrypted_password, sp->sp_pwdp) != 0) {
        printf("Incorrect Confirm Password\n");
        return 1;
    }
    
    // Changes the user's email in the shadow file
    char* new_shadow_entry = malloc(strlen(new_email) + strlen(encrypted_password) + 2);
    sprintf(new_shadow_entry, "%s:%s", new_email, encrypted_password);
    setspent();
    struct spwd *temp;
    while ((temp = getspent()) != NULL) {
        if (strcmp(old_email, temp->sp_namp) == 0) {
            endspent();
            printf("Successfully changed email from %s to %s\n", old_email, new_email);
            return 0;
        }
    }
    
    // If the user's old email is not found in the shadow file, something has gone wrong
    endspent();
    free(new_shadow_entry);
    printf("Something went wrong\n");
    return 1;
}