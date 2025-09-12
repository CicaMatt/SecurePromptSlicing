#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_FILE "subscribers.txt"
#define UNSUBSCRIBE_MESSAGE "User unsubscribed successfully."
#define NOT_SUBSCRIBED_MESSAGE "The email is not subscribed."

typedef struct {
    char email[256];
} Subscriber;

int read_subscriber_count(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;
    
    int count = 0;
    while (fscanf(file, "%255s\n", NULL) != EOF) {
        count++;
    }
    
    fclose(file);
    return count;
}

Subscriber* load_subscribers(const char *filename, int count) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    
    Subscriber *subscribers = (Subscriber *)malloc(sizeof(Subscriber) * count);
    for (int i = 0; i < count && fscanf(file, "%255s\n", subscribers[i].email); ++i);
    
    fclose(file);
    return subscribers;
}

void save_subscribers(const char *filename, Subscriber *subscribers, int count) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < count; ++i) {
        fprintf(file, "%s\n", subscribers[i].email);
    }
    
    fclose(file);
}

int find_and_delete_subscriber(Subscriber *subscribers, int count, const char *email_to_unsubscribe) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(subscribers[i].email, email_to_unsubscribe) == 0) {
            memmove(&subscribers[i], &subscribers[i + 1], sizeof(Subscriber) * (count - i - 1));
            return count - 1;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email_to_unsubscribe>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email_to_unsubscribe = argv[1];
    
    int subscriber_count = read_subscriber_count(DATABASE_FILE);
    if (subscriber_count == 0) {
        printf("%s\n", NOT_SUBSCRIBED_MESSAGE);
        return EXIT_SUCCESS;
    }
    
    Subscriber *subscribers = load_subscribers(DATABASE_FILE, subscriber_count);
    if (!subscribers) {
        fprintf(stderr, "Error loading subscribers.\n");
        return EXIT_FAILURE;
    }

    int new_count = find_and_delete_subscriber(subscribers, subscriber_count, email_to_unsubscribe);
    if (new_count == subscriber_count) {
        printf("%s\n", NOT_SUBSCRIBED_MESSAGE);
    } else {
        save_subscribers(DATABASE_FILE, subscribers, new_count);
        printf("%s\n", UNSUBSCRIBE_MESSAGE);
    }

    free(subscribers);
    return EXIT_SUCCESS;
}