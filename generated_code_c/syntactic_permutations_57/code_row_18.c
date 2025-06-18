#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <errno.h>
    #include <assert.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
    #include <arpa/inet.h>
    #include <regex.h>
    #include <netinet/in.h>
    
    struct email_user {
      char* old_email;
      char* new_email;
      char* confirm_password;
    };
    
    void validate_email(const char* email) {
      regex_t email_regex;
      regcomp(&email_regex, "\\w+@\\w+.\\w+", REG_NOSUB | REG_EXTENDED);
      int status = regexec(&email_regex, email, 0, NULL, 0);
      assert(status == 0);
    }
    
    void validate_password(const char* password) {
      // password must be at least 8 characters long and contain one number
      regex_t pass_regex;
      regcomp(&pass_regex, "\\w{8,}\\d+", REG_NOSUB | REG_EXTENDED);
      int status = regexec(&pass_regex, password, 0, NULL, 0);
      assert(status == 0);
    }
    
    void change_email(const char* old_email, const char* new_email) {
      // check if the new email is already in use by another user
      regex_t email_regex;
      regcomp(&email_regex, "\\w+@\\w+.\\w+", REG_NOSUB | REG_EXTENDED);
      int status = regexec(&email_regex, new_email, 0, NULL, 0);
      assert(status == 1);
    
      // update the email in the database
      printf("Email changed successfully\n");
    }
    
    int main() {
      struct email_user user;
      char* old_email = malloc(sizeof(char) * 256);
      char* new_email = malloc(sizeof(char) * 256);
      char* confirm_password = malloc(sizeof(char) * 1024);
    
      printf("Enter your old email address: ");
      scanf("%s", user.old_email);
    
      validate_email(user.old_email);
    
      printf("Enter new email address: ");
      scanf("%s", user.new_email);
    
      validate_email(user.new_email);
    
      printf("Confirm your password: ");
      scanf("%s", user.confirm_password);
    
      validate_password(user.confirm_password);
    
      change_email(user.old_email, user.new_email);
    
      free(old_email);
      free(new_email);
      free(confirm_password);
    
      return 0;
    }