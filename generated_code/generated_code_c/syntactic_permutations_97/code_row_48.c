// Import the necessary dependencies
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    
    int main() {
      MYSQL *conn;
      MYSQL_RES *res;
      MYSQL_ROW row;
    
      char *server = "localhost";
      char *user = "root";
      char *password = "root"; 
      char *database = "example";
    
      // Initialize the database connection
      conn = mysql_init(NULL);
    
      // Connect to the database
      if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        exit(1);
      }
    
      // User input variables
      char username[256];
      char password[256];
      char firstName[256];
      char lastName[256];
      char email[256];
    
      printf("Enter username: ");
      fgets(username, 256, stdin);
      username[strcspn(username, "\n")] = '\0';
    
      printf("Enter password: ");
      fgets(password, 256, stdin);
      password[strcspn(password, "\n")] = '\0';
    
      printf("Enter first name: ");
      fgets(firstName, 256, stdin);
      firstName[strcspn(firstName, "\n")] = '\0';
    
      printf("Enter last name: ");
      fgets(lastName, 256, stdin);
      lastName[strcspn(lastName, "\n")] = '\0';
    
      printf("Enter email: ");
      fgets(email, 256, stdin);
      email[strcspn(email, "\n")] = '\0';
    
      // Hash the password using SHA-256 algorithm
      char hashedPassword[32];
      strcpy(hashedPassword, sha256(password).c_str());
    
      // Insert user data into the database
      char query[1024] = "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('";
      strcat(query, username);
      strcat(query, "', '");
      strcat(query, hashedPassword);
      strcat(query, "', '");
      strcat(query, firstName);
      strcat(query, "', '");
      strcat(query, lastName);
      strcat(query, "', '");
      strcat(query, email);
      strcat(query, "')");
    
      // Execute the query
      if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        exit(1);
      }
    
      // Check if username already exists in the database
      char selectQuery[1024] = "SELECT * FROM users WHERE username='";
      strcat(selectQuery, username);
      strcat(selectQuery, "'");
    
      // Execute the query
      if (mysql_query(conn, selectQuery)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        exit(1);
      }
    
      res = mysql_store_result(conn);
      int numRows = mysql_num_rows(res);
    
      if (numRows > 0) {
        printf("Username already exists\n");
      } else {
        printf("Registration successful\n");
      }
    
      // Clean up
      mysql_free_result(res);
      mysql_close(conn);
    }