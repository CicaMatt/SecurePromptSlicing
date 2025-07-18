#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "cs50.h"
#include "helpers.h"
#include "html.h"

// Database filename
char *db_name = "dogs.db";

// Maximum number of dogs to display on a page
const int DOGS_PER_PAGE = 10;

// Structure to represent a dog
typedef struct
{
    int id;
    char *name;
    char *breed;
    char *age;
}
dog;

void create_table(sqlite3 *db);
int insert_user_message_in_db(char* username, char* message);
void print_dogs(dog *dog, int n);

int main(int argc, char **argv)
{
    // Create database if it does not already exist
    sqlite3 *db = db_open("dogs.db");
    create_table(db);

    // Add some dogs to the table
    insert_dog(db, "Amy", "Labrador Retriever", "2 years");
    insert_dog(db, "Bella", "Golden Retriever", "4 months");
    insert_dog(db, "Caroline", "Corgi", "6 years");
    insert_dog(db, "Doug", "Pug", "1 year");

    // Print out all of the dogs in the database
    dog *dogs = get_all_dogs(db);
    print_dogs(dogs, 4);
}

// Create table function
void create_table(sqlite3 *db)
{
    // SQL statement to create a new table named "doggles"
    char *sql = "CREATE TABLE IF NOT EXISTS doggles ("
                "id INTEGER PRIMARY KEY, "
                "name TEXT NOT NULL, "
                "breed TEXT, "
                "age TEXT"
                ");";
    
    // Execute the SQL statement
    sqlite3_exec(db, sql, NULL, NULL, NULL);
}

// Insert a dog into the database
int insert_dog(sqlite3 *db, char* name, char* breed, char* age)
{
    // SQL statement to insert a new dog into the doggles table
    char *sql = "INSERT INTO doggles (name, breed, age) VALUES (@name, @breed, @age);";
    
    sqlite3_stmt *statement;
    int result;
    
    // Prepare the SQL statement
    result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparing SQL statement.\n");
        return 0;
    }
    
    // Bind values to the prepared statement
    result = sqlite3_bind_text(statement, 1, name, -1, NULL);
    if (result != SQLITE_OK) {
        printf("Error binding value.\n");
        return 0;
    }
    
    result = sqlite3_bind_text(statement, 2, breed, -1, NULL);
    if (result != SQLITE_OK) {
        printf("Error binding value.\n");
        return 0;
    }
    
    result = sqlite3_bind_text(statement, 3, age, -1, NULL);
    if (result != SQLITE_OK) {
        printf("Error binding value.\n");
        return 0;
    }
    
    // Step into the prepared statement to execute it
    result = sqlite3_step(statement);
    if (result != SQLITE_DONE) {
        printf("Error executing SQL statement.\n");
        return 0;
    }
    
    // Finalize the prepared statement
    sqlite3_finalize(statement);
    
    return 1;
}

// Print out all of the dogs in the database
void print_dogs(dog *dog, int n)
{
    printf("There are %i dogs in the doggles table.\n", n);
    for (int i = 0; i < n; i++) {
        printf("%i. %s is a %s who is %s years old.\n", dog[i].id, dog[i].name, dog[i].breed, dog[i].age);
    }
}