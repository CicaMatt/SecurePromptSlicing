// GET Request
void login()
{
  printf("\n\tLogin Form:\n");
  printf("Username: ");
  scanf("%s", username);
  printf("\nPassword: ");
  scanf("%s", password);
}

// POST request
void do_login(char *username, char *password)
{
  if (strcmp(admin_user, username) == 0 && strcmp(admin_pass, password) == 0)
  {
    redirect("/admin");
  }
}