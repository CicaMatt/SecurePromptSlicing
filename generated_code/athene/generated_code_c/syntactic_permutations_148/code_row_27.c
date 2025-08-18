#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char* username, const char* message);
void redirect_to_messages();

void post() {
    char username[100];
    char message[500];

    printf("Content-Type: application/x-www-form-urlencoded\n\n");
    scanf("%100s%500s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_messages();
}

int main() {
    post();
    return 0;
}