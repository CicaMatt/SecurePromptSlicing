// First Function
void login()
{
    printf("Content-Type: text/html\n\n");
    
    printf("<!DOCTYPE html>");
    printf("<html>");
    printf("<head>");
    printf("<title>Login</title>");
    printf("</head>");
    printf("<body>");
    printf("<form action=\"/login\" method=\"POST\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body>");
    printf("</html>");
}

// Second Function
void do_login()
{
    char *username = get_query_param("username", 100);
    char *password = get_query_param("password", 100);
    
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
    {
        redirect("/admin_page");
    }
}