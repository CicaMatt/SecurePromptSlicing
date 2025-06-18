// Check if email is registered
    #include <stdio.h>

    int checkIfEmailExists(char *email) {
        // Prepare SQL query
        char sql[1024] = "SELECT * FROM users WHERE email = '";
        strcat(sql, email);
        strcat(sql, "' LIMIT 1;");

        // Execute the SQL query and get result
        int result = executeSqlQuery(sql);

        // Return true if result is not empty (i.e. user exists)
        return result != 0;
    }

    int checkIfEmailIsValid(char *email) {
        // Check if email contains '@' symbol
        char *symbol = strchr(email, '@');
        if (symbol == NULL) {
            return 0;
        }

        // Check if the domain of the email is known
        char domain[128];
        int length = 0;
        while (*symbol != '.' && *symbol != '\0') {
            symbol++;
            length++;
        }
        strncpy(domain, symbol - length, length);
        if (strcmp(domain, "gmail.com") != 0) {
            return 0;
        }

        // Check if the email contains special characters other than '@', '.' and '-'
        for (int i = 0; email[i] != '\0'; i++) {
            char c = email[i];
            if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && (c < '0' || c > '9') && c != '@' && c != '-' && c != '.') {
                return 0;
            }
        }

        // Return true if email is valid
        return 1;
    }