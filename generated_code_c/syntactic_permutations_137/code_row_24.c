#include <stdio.h>
    #include <string.h>
    
    int check_mod(char* username, char* password, char* session) {
      return auth_mod(username, password, session);
    }
    
    int main() {
      printf("Hello, World! %d\n", check_mod("user1", "pass2", "sess3"));
      return 0;
    }