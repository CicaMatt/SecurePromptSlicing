#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>

int main(int argc, char *argv[]) {
	MYSQL_ROW row;

	// Connect to database
	MYSQL *connection = mysql_init(NULL);

	if (!mysql_real_connect(connection, "localhost", "username", "password", "database_name", 3306, NULL, 0)) {
		printf("Error connecting to database\n");
		return 1;
	}

	// Create user table if it doesn't already exist
	mysql_query(connection, "CREATE TABLE IF NOT EXISTS users (id INT AUTO_INCREMENT PRIMARY KEY, username VARCHAR(255), password VARCHAR(255))");

	char *username = NULL;
	char *password = NULL;

	// Prompt for user input
	printf("Enter a username: ");
	scanf("%s", &username);
	printf("Enter a password: ");
	scanf("%s", &password);

	// Insert username and hashed password into database
	char query[256];
	sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, sha1(password));
	if (mysql_query(connection, query)) {
		printf("Error inserting data\n");
		return 1;
	}

	// Clean up
	free(username);
	free(password);

	mysql_close(connection);

	return 0;
}