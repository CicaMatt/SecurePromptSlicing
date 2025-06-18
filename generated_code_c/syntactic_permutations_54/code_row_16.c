// login page for user
    void login() {
      printf("Enter Username: ");
      scanf("%s", username);
      printf("Enter Password: ");
      scanf("%s", password);
      do_login(username, password);
    }
    // function to check for admin
    void do_login(char* username, char* password) {
      if (strcmp(username, "admin") && strcmp(password, "pass")) {
        redirect("https://www.example.com/admin");
      } else {
        return;
      }
    }