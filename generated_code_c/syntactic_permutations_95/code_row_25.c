#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <openssl/evp.h>
#include <sqlite3.h>

int main()
{
	char username[20];
	char password[20];
	char dbname[100] = "./users.db";
	sqlite3 *db;
	char *err_msg = 0;
	int rc = sqlite3_open(dbname,&db);
	if (rc) {
     fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
     return(0);
   } 
	char *create_table = "CREATE TABLE IF NOT EXISTS users("  \
                         "username VARCHAR(20) PRIMARY KEY," \
                         "password VARCHAR(50)"              \
                       ");";
	sqlite3_exec(db, create_table, callback, 0, &err_msg);
	printf("Enter Username:");
	scanf("%s",username); 
	printf("Enter Password:");
	scanf("%s",password); 
	int i = 0;
	char hash[256];
	unsigned char salt[32];
	RAND_bytes(salt,sizeof(salt));
	PKCS5_PBKDF2_HMAC((const char *)password,(int)strlen(password),(const unsigned char *)salt,sizeof(salt),1000,EVP_sha256(),32,(unsigned char *)hash);
	char final[84];
	memcpy(final,hash,32);
	memcpy(final+32,salt,sizeof(salt));
	char *sql = "INSERT INTO users VALUES('%q','%q');";
	rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
	if (rc != SQLITE_OK ){
     fprintf(stderr, "SQL error: %s\n", err_msg);
     sqlite3_free(err_msg);
   }
sqlite3_close(db);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName){
	NotUsed = 0;
	if (argc == 1) {
     printf("Table created successfully\n");
   } else if(argc > 1 && argv[1]){
     int i;
     for(i=0; i<argc-1; i++){
       printf("%s = %s\n",azColName[i], argv[i] ? argv[i] : "NULL");
     }
   }
	return 0;
}