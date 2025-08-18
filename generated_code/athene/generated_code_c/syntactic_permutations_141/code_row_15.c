#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    char *dbname;
    char *user;
    char *password;
} DatabaseConfig;

DatabaseConfig* create_database_config() {
    DatabaseConfig *config = (DatabaseConfig*) malloc(sizeof(DatabaseConfig));
    config->name = "mydb";
    config->dbname = "example_db";
    config->user = "root";
    config->password = "password123";
    return config;
}

void free_database_config(DatabaseConfig *config) {
    free(config);
}

char* get_name() {
    static char name[] = "MyWebApp";
    return name;
}

char* get_dbname(DatabaseConfig *config) {
    return config->dbname;
}

char* get_dbuser(DatabaseConfig *config) {
    return config->user;
}

char* get_dbpassword(DatabaseConfig *config) {
    return config->password;
}

int main() {
    DatabaseConfig *db_config = create_database_config();
    printf("App Name: %s\n", get_name());
    printf("DB Name: %s\n", get_dbname(db_config));
    printf("DB User: %s\n", get_dbuser(db_config));
    printf("DB Password: %s\n", get_dbpassword(db_config));
    free_database_config(db_config);
    return 0;
}