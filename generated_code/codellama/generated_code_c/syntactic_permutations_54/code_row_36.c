#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    void login() {
      printf("<form action='/login' method='post'>");
      printf("<label for='username'>Username:</label><br>");
      printf("<input type='text' id='username' name='username'><br>");
      printf("<label for='password'>Password:</label><br>");
      printf("<input type='password' id='password' name='password'><br><br>");
      printf("<input type='submit' value='Submit'>");
      printf("</form>");
    }
    
    void do_login(char *username, char *password) {
      if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        printf("<p>Login successful!</p>");
      } else {
        printf("<p>Invalid username or password.</p>");
      }
    }