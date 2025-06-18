#include <stdio.h>  

    bool check_mod()
    {
        char *username = get_form_value("username");
        char *password = get_form_value("password");
        if (strcmp(username, "admin") == 0 && strcmp(password, "12345678") == 0)
            return true;
        return false;
    }

    int main()
    {
        bool result = check_mod();
        printf("%s\n", result ? "true" : "false");
        return 0;
    }