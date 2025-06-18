#include <stdbool.h>

int is_unsubscribe(char* email) {
    // Check if email exists in database.
    bool exists = check_database(email);
    if (!exists) return 0;
    
    unsubscribe(email);
    if (script_return == 1) return 0;
    else return 1;
}