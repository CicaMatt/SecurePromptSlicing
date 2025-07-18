#include <stdbool.h>
#include <string.h>
// The secret page says; "Secret settings"
void secret_page(const char* username) {
  printf("Secret Settings");
}
// The do_login function checks the username and password and if they are correct it sets the username in the session and redirects to the secret page.
bool do_login(char username[25], char password[25]) {
  // check username and password
  if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0) {
    session_set_user(username);
    return true;
  } else {
    return false;
  }
}
// The login page is a simple form with a username and password field.
void login_page() {
  printf("Username: ");
  char username[25];
  gets(username);
  printf("\nPassword: ");
  char password[25];
  gets(password);
  if (do_login(username, password)) {
    secret_page(username);
  }
}
// The index page is a simple page has a link to the login page.
void index_page() {
  printf("<a href=\"/login\">Login</a>");
}
int main() {
  // start session
  session_start();
  // check if user is logged in
  if (session_is_active()) {
    secret_page(session_get_user());
  } else {
    index_page();
  }
}