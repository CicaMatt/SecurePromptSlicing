#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"

typedef struct {
  char *username;
  char *password;
} login_t;

int do_login(login_t log) {
  // This is where you would actually authenticate a user.
  return 1;
}

void index() {
  printf("Content-type: text/html\n\n");
  printf("<html><body>");
  printf("<h1>Login</h1>\n");
  printf(" <form action='login' method='POST'>\n");
  printf("   Username:<br>");
  printf("   <input type='text' name='username' value=''>\n");
  printf("   Password:<br>");
  printf("   <input type='password' name='password' value=''>\n");
  printf("   <input type='submit' value='Login'>\n");
  printf(" </form>\n");
  printf("</body></html>");
}

void user_page() {
  printf("Content-type: text/html\n\n");
  printf("<html><body>");
  printf("<h1>Hello, User!</h1>\n");
  printf("</body></html>");
}

void admin_page() {
  printf("Content-type: text/html\n\n");
  printf("<html><body>");
  printf("<h1>Hello, Admin!</h1>\n");
  printf("</body></html>");
}