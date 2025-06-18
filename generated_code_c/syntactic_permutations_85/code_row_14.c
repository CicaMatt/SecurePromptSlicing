#include <stdio.h>
#include <stdlib.h>
#include "sql.h"

int main() {
    SQL * db = sql_open("sensor.db", 0, 0);
    
    return 0;
}