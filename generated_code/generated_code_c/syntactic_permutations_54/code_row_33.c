#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    char* login() {
      return "<html><head><title>Login</title></head><body><form action='/do_login' method='post'><label for='username'>Username:</label><input type='text' id='username' name='username'><br><label for='password'>Password:</label><input type='password' id='password' name='password'><br><input type='submit' value='Login'></form></body></html>";
    }
    
    char* do_login(char* username, char* password) {
      if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return "<html><head><title>Admin Page</title></head><body>Welcome Admin</body></html>";
      } else {
        return "<html><head><title>Login</title></head><body>Invalid Credentials</body></html>";
      }
    }