#include <stdio.h>
    #include <string.h> /* for strcmp() */

    /* define constants and macros */
    #define PASS_SIZE 50
    #define SALT_SIZE 64
    #define HASHED_PASSWORD_SIZE 64

    /* define user structure */
    typedef struct {
        char username[20];
        unsigned char password[HASHED_PASSWORD_SIZE];
    } User;

    /* function prototypes */
    void get_username(User* user);
    void get_password(User* user, const unsigned char salt[SALT_SIZE]);
    void hash_password(const char password[PASS_SIZE],
                       const unsigned char salt[SALT_SIZE],
                       unsigned char hashed_password[HASHED_PASSWORD_SIZE]);

    int main() {
        User user = {"", {}};

        /* get username from user */
        printf("Enter your username: ");
        get_username(&user);

        /* create a random salt and hash the password */
        unsigned char salt[SALT_SIZE];
        srandom(time(NULL));
        for (int i = 0; i < SALT_SIZE; ++i) {
            salt[i] = random() & 255;
        }
        get_password(&user, salt);

        /* print the hashed password */
        printf("Hashed password: ");
        for (int i = 0; i < HASHED_PASSWORD_SIZE; ++i) {
            printf("%02x", user.password[i]);
        }
        printf("\n");
    }

    void get_username(User* user) {
        char buf[20];
        scanf("%19s", buf);
        strcpy(user->username, buf);
    }

    void get_password(User* user, const unsigned char salt[SALT_SIZE]) {
        char password[PASS_SIZE];
        printf("Enter your password: ");
        scanf("%59s", password);
        hash_password(password, salt, user->password);
    }

    void hash_password(const char password[PASS_SIZE],
                       const unsigned char salt[SALT_SIZE],
                       unsigned char hashed_password[HASHED_PASSWORD_SIZE]) {
        /* do hashing here */
    }