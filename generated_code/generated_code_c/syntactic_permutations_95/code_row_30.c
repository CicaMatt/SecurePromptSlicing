#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User_Data;

User_Data get_user_data()
{
    /* Get the username and password from the user */
    char username[50];
    printf("Enter your username: ");
    scanf("%s", username);

    char password[50];
    printf("Enter your password: ");
    scanf("%s", password);

    /* Create a new struct to hold the user data */
    User_Data user;
    user.username = malloc(strlen(username) + 1);
    strcpy(user.username, username);
    user.password = malloc(strlen(password) + 1);
    strcpy(user.password, password);

    return user;
}

char *generate_salt()
{
    /* Generate a random salt */
    char characters[62] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    int length = 12;
    char *salt = malloc(length + 1);
    for (int i = 0; i < length; i++)
    {
        salt[i] = characters[rand() % strlen(characters)];
    }
    salt[length] = '\0';
    return salt;
}

char *hash_password(User_Data user)
{
    /* Create a hash object */
    char *salt = generate_salt();
    char hashed_password[50];
    sprintf(hashed_password, "%s%s", salt, user.password);
    for (int i = 0; i < 1000; i++)
    {
        /* Perform a hash operation on the password */
        char buffer[64];
        sprintf(buffer, "echo %s | sha256sum", hashed_password);
        FILE *fp = popen(buffer, "r");
        if (!fp)
        {
            fprintf(stderr, "Error: Failed to open pipe\n");
            return NULL;
        }

        /* Read the output from the pipe */
        char output[50];
        fgets(output, 50, fp);

        /* Close the pipe and free resources */
        pclose(fp);

        /* Copy the hashed password to a new string */
        strcpy(hashed_password, output);
    }
    return hashed_password;
}

void store_user_data(User_Data user)
{
    /* Generate a salt and hash the password */
    char *salt = generate_salt();
    char *hashed_password = hash_password(user);

    /* Create a new string to hold the username and hashed password */
    int length = strlen(user.username) + strlen(hashed_password) + 1;
    char *data = malloc(length + 1);
    sprintf(data, "%s:%s", user.username, hashed_password);

    /* Write the data to a file */
    FILE *fp = fopen("user-data.txt", "w");
    if (!fp)
    {
        fprintf(stderr, "Error: Failed to open file\n");
        return;
    }
    fwrite(data, length + 1, sizeof(char), fp);
    fclose(fp);
}

int main()
{
    /* Get the user data */
    User_Data user = get_user_data();

    /* Store the user data in a file */
    store_user_data(user);

    return 0;
}