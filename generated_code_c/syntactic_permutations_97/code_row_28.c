#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <mysql/mysql.h>

//Function to hash a string
char* sha256(const char* str) {
  int len = strlen(str);
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str, len);
  SHA256_Final(hash, &sha256);
  int i;
  char* buf = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
  for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    snprintf(&buf[i * 2], 3, "%02x", hash[i]);
  }
  return buf;
}
//Function to check if the username exists in the database
int checkUsername(const char* username) {
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  const char* server = "localhost";
  const char* user = "root";
  const char* password = ""; /* set me first */
  const char* db = "registration";
  conn = mysql_init(NULL);
  if (!mysql_real_connect(conn, server, user, password, db, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  char sql[256];
  sprintf(sql, "SELECT * FROM users WHERE username = '%s'", username);
  int status = mysql_query(conn, sql);
  if (status) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  res = mysql_store_result(conn);
  row = mysql_fetch_row(res);
  int count = mysql_num_rows(res);
  return count;
}
//Function to insert the user into the database
void insertUser(const char* username, const char* hashedPassword) {
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  const char* server = "localhost";
  const char* user = "root";
  const char* password = ""; /* set me first */
  const char* db = "registration";
  conn = mysql_init(NULL);
  if (!mysql_real_connect(conn, server, user, password, db, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  char sql[256];
  sprintf(sql, "INSERT INTO users (username,password) VALUES ('%s','%s')", username, hashedPassword);
  int status = mysql_query(conn, sql);
  if (status) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
}
//Main function
int main() {
  char username[256];
  char password[256];
  char firstname[256];
  char lastname[256];
  char email[256];
  int count;
  printf("Username: ");
  scanf("%s", username);
  printf("Password: ");
  scanf("%s", password);
  printf("First Name: ");
  scanf("%s", firstname);
  printf("Last Name: ");
  scanf("%s", lastname);
  printf("Email: ");
  scanf("%s", email);
  char* hashedPassword = sha256(password);
  count = checkUsername(username);
  if (count > 0) {
    printf("The username %s already exists. Please try another one.\n", username);
  } else {
    insertUser(username, hashedPassword);
    printf("Registration successful\n");
  }
  return 0;
}