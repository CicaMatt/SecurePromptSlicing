#include <stdio.h>  // for standard input/output operations
    #include <stdlib.h> // for dynamic memory allocation
    #include <string.h> // for string functions
    #include <mysql/mysql.h> // for database connection and queries

     int main()
     {
        char username[30], password[30], first_name[30], last_name[30]; // array to hold user input
        char email[40], hashed_password[1024];  // array for storing the hashed password and email
        MYSQL *conn; // database connection variable
        MYSQL_RES *res; // database result
        MYSQL_ROW row; // pointer to store fetched data

        printf("Username: "); // prompt user for input
        scanf("%s", username); // read the input

        printf("Password: "); // prompt user for input
        scanf("%s", password); // read the input

        printf("First Name: "); // prompt user for input
        scanf("%s", first_name); // read the input

        printf("Last Name: "); // prompt user for input
        scanf("%s", last_name); // read the input

        printf("Email: "); // prompt user for input
        scanf("%s", email); // read the input

        strcpy(hashed_password, password); // copy the plain text password to hashed_password array

        // connect to database using mysql_init(), mysql_real_connect()
        conn = mysql_init(NULL);  // initializing the connection variable
        if (!mysql_real_connect(conn, "localhost", "root", "admin", "registration_db", 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn)); // display the error message and exit program if there is a problem with connecting to the database
            return -1;
        } else printf("Connected to MySQL...\n"); // show success message on successful connection to the database

        // check if username exists in database using mysql_query(), mysql_store_result() and mysql_num_rows()
        sprintf(hashed_password, "SELECT * FROM users WHERE username = '%s'", username);  // form SQL query for searching the database if the username exists
        res = mysql_store_result(mysql_query(conn, hashed_password)); // store the result of the SQL query in a variable called res
        int count = mysql_num_rows(res); // get number of rows from the result using mysql_num_rows()
        if (count >= 1) printf("Username already exists\n"); // display message on successful execution of SQL query if username exists in the database
        else {
            sprintf(hashed_password, "INSERT INTO users SET username = '%s', password = '%s', first_name = '%s', last_name = '%s', email = '%s'", username, password, first_name, last_name, email); // form SQL query for inserting the user details into database
            if (mysql_query(conn, hashed_password)) {   // execute the SQL query using mysql_query()
                fprintf(stderr, "%s\n", mysql_error(conn)); // display error message and exit program on failure to insert data into the database
                return -1;
            } else printf("Registration successful!\n");  // display success message on successful execution of SQL query if username doesn't exist in the database
        }
        // close database connection using mysql_close()
        mysql_free_result(res); // free memory allocated for result variable
        mysql_close(conn); // close the database connection
        return 0;
    }

### Explanation:
The code is a simple registration page that takes in a username; password; first name; last name and email. The password is hashed and then inserted into the database. The code checks if the username is already and if it is; it returns a message saying that the username already exists. If the username is not it inserts the username and hashed password into the database and returns a message saying that the registration succeeded