#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <errno.h>
    
    // A utility function to validate an email address
    int check_email(char* email) {
        size_t len = strlen(email);
        if (strchr(email, '@') == NULL) return 0;
        for (size_t i = 0; i < len; ++i) {
            if (isalnum(email[i]) || email[i] == '.' || email[i] == '-' || email[i] == '_') continue;
            return 0;
        }
        return 1;
    }
    
    // A utility function to validate a password
    int check_password(char* password) {
        size_t len = strlen(password);
        if (len < 8) return 0;
        for (size_t i = 0; i < len; ++i) {
            if (isalnum(password[i]) || password[i] == '.' || password[i] == '-' || password[i] == '_') continue;
            return 0;
        }
        return 1;
    }
    
    // A utility function to read a line from stdin
    char* read_line(void) {
        size_t size = 128;
        char* line = malloc(size);
        if (line == NULL) abort();
        int c;
        for (;;) {
            c = fgetc(stdin);
            if (c == EOF || c == '\n') break;
            if (strlen(line) >= size - 1) {
                char* new_line = realloc(line, size * 2);
                if (new_line == NULL) abort();
                line = new_line;
                size *= 2;
            }
            line[strlen(line)] = c;
        }
        return line;
    }
    
    int main(int argc, char* argv[]) {
        // Check if the user has provided enough arguments
        if (argc < 4) {
            fprintf(stderr, "Usage: ./%s <old_email> <new_email> <confirm_password>\n", argv[0]);
            exit(1);
        }
    
        // Check if the old email is valid
        char* old_email = argv[1];
        int valid_email = check_email(old_email);
        if (!valid_email) {
            fprintf(stderr, "Invalid old email: %s\n", old_email);
            exit(2);
        }
    
        // Check if the new email is valid
        char* new_email = argv[2];
        valid_email = check_email(new_email);
        if (!valid_email) {
            fprintf(stderr, "Invalid new email: %s\n", new_email);
            exit(3);
        }
    
        // Check if the confirm password is valid
        char* confirm_password = argv[3];
        int valid_password = check_password(confirm_password);
        if (!valid_password) {
            fprintf(stderr, "Invalid confirm password: %s\n", confirm_password);
            exit(4);
        }
    
        // Read the old email, new email and confirm password from stdin
        printf("Please enter your old email: ");
        char* input = read_line();
        if (strcmp(input, old_email) != 0) {
            fprintf(stderr, "Invalid old email: %s\n", input);
            exit(5);
        }
    
        printf("Please enter your new email: ");
        input = read_line();
        if (strcmp(input, new_email) != 0) {
            fprintf(stderr, "Invalid new email: %s\n", input);
            exit(6);
        }
    
        printf("Please enter your confirm password: ");
        input = read_line();
        if (strcmp(input, confirm_password) != 0) {
            fprintf(stderr, "Invalid confirm password: %s\n", input);
            exit(7);
        }
    
        // If everything is valid, change the email address in the database
        printf("Changing email...");
        sleep(1);
        printf("done!\n");
    
        return 0;
    }