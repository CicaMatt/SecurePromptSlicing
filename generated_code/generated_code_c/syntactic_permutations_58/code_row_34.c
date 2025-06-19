#include <stdio.h>

int main() {
  char old_email[50];
  char new_email[50];
  char password[128];
  int logged_in = 0;
  int email_changed = 0;

  printf("Enter your old email: ");
  scanf("%s", old_email);
  printf("\n");

  if (logged_in == 1) {
    printf("Enter your new email: ");
    scanf("%s", new_email);
    printf("\n");

    printf("Enter your password to confirm: ");
    scanf("%s", password);
    printf("\n");

    if (password == "correct") {
      email_changed = 1;
    }
  } else {
    printf("You are not logged in.\n");
  }

  if (email_changed == 1) {
    printf("%s\n", new_email);
  } else {
    printf("%s\n", old_email);
  }
}