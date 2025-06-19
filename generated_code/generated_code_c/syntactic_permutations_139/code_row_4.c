#include <stdio.h> 
#include <stdlib.h> 
#include "sqlite3.h" 
void main() { 
char* data = getenv("DATA"); 
if (!data) { 
printf("No credentials found. Exiting."); 
exit(1); 
} 
sqlite3 *db; 
sqlite3_stmt * stmt; 
const char *tail; 
int rc = sqlite3_open(data, &db); 
if (rc != SQLITE_OK) { 
fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db)); 
sqlite3_close(db); 
exit(1); 
} 
const char *sql = "SELECT is_moderator FROM users WHERE user_id = ?"; 
rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail); 
if (rc != SQLITE_OK) { 
fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db)); 
sqlite3_close(db); 
exit(1); 
} 
const char *user_id = getenv("USER_ID"); 
rc = sqlite3_bind_text(stmt, 1, user_id, -1, SQLITE_STATIC); 
if (rc != SQLITE_OK) { 
fprintf(stderr, "Binding failed: %s\n", sqlite3_errmsg(db)); 
sqlite3_close(db); 
exit(1); 
} 
rc = sqlite3_step(stmt); 
if (rc != SQLITE_ROW) { 
fprintf(stderr, "Query failed: %s\n", sqlite3_errmsg(db)); 
sqlite3_close(db); 
exit(1); 
} 
int is_moderator = sqlite3_column_int(stmt, 0); 
if (is_moderator) { 
printf("true\n"); 
} else { 
printf("false\n"); 
} 
sqlite3_finalize(stmt); 
sqlite3_close(db); 
exit(0); 
}