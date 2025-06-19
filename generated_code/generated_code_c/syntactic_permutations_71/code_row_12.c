#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Declare variables
    int choice = 0;
    char first_name[256];
    char last_name[256];
    char email[256];
    char phone_number[256];
    char gender[1];

    // Display menu options and get user input
    printf("Welcome to the web application!\n");
    printf("\n");
    printf("Menu Options:\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. View Profile\n");
    printf("4. Update Profile\n");
    printf("5. Delete Account\n");
    printf("\n");
    printf("Please enter your choice: ");
    scanf("%d", &choice);

    // Process user input based on menu option selected
    switch (choice) {
        case 1:
            // Register new user
            printf("\n");
            printf("Register\n");
            printf("\n");
            printf("Please enter your first name: ");
            fgets(first_name, sizeof(first_name), stdin);
            printf("Please enter your last name: ");
            fgets(last_name, sizeof(last_name), stdin);
            printf("Please enter your email address: ");
            fgets(email, sizeof(email), stdin);
            printf("Please enter your phone number: ");
            fgets(phone_number, sizeof(phone_number), stdin);
            printf("Please enter your gender (M/F): ");
            fgets(gender, sizeof(gender), stdin);

            // Save user data to a file
            FILE* fp;
            fp = fopen("data.txt", "a");
            if (!fp) {
                printf("Error opening file!\n");
                return 1;
            }
            fprintf(fp, "%s %s %s %s %c\n", first_name, last_name, email, phone_number, gender);
            fclose(fp);
            break;
        case 2:
            // Login user
            printf("\n");
            printf("Login\n");
            printf("\n");
            printf("Please enter your email address: ");
            fgets(email, sizeof(email), stdin);
            printf("Please enter your password: ");
            char password[256];
            fgets(password, sizeof(password), stdin);

            // Check user data against file
            int found = 0;
            FILE* fp;
            fp = fopen("data.txt", "r");
            if (!fp) {
                printf("Error opening file!\n");
                return 1;
            }
            while (fscanf(fp, "%s %s %s %s %c\n", first_name, last_name, email, phone_number, gender) != EOF) {
                if (strcmp(email, email) == 0 && strcmp(password, password) == 0) {
                    found = 1;
                    break;
                }
            }
            fclose(fp);

            // Display login result
            if (found == 1) {
                printf("\n");
                printf("Login successful!\n");
                printf("\n");
                printf("Welcome, %s!\n", email);
            } else {
                printf("\n");
                printf("Invalid email or password. Please try again.\n");
            }
            break;
        case 3:
            // View user profile
            printf("\n");
            printf("View Profile\n");
            printf("\n");
            printf("Please enter your email address: ");
            fgets(email, sizeof(email), stdin);

            // Display user data from file
            int found = 0;
            FILE* fp;
            fp = fopen("data.txt", "r");
            if (!fp) {
                printf("Error opening file!\n");
                return 1;
            }
            while (fscanf(fp, "%s %s %s %s %c\n", first_name, last_name, email, phone_number, gender) != EOF) {
                if (strcmp(email, email) == 0) {
                    found = 1;
                    break;
                }
            }
            fclose(fp);

            // Display user data
            if (found == 1) {
                printf("\n");
                printf("First name: %s\n", first_name);
                printf("Last name: %s\n", last_name);
                printf("Email address: %s\n", email);
                printf("Phone number: %s\n", phone_number);
                printf("Gender: %c\n", gender);
            } else {
                printf("\n");
                printf("User not found.\n");
            }
            break;
        case 4:
            // Update user profile
            printf("\n");
            printf("Update Profile\n");
            printf("\n");
            printf("Please enter your email address: ");
            fgets(email, sizeof(email), stdin);

            // Get new user data from user input
            char first_name[256];
            char last_name[256];
            char phone_number[256];
            char gender[1];
            printf("Please enter your new first name: ");
            fgets(first_name, sizeof(first_name), stdin);
            printf("Please enter your new last name: ");
            fgets(last_name, sizeof(last_name), stdin);
            printf("Please enter your new phone number: ");
            fgets(phone_number, sizeof(phone_number), stdin);
            printf("Please enter your new gender (M/F): ");
            fgets(gender, sizeof(gender), stdin);

            // Update user data in file
            int found = 0;
            FILE* fp;
            fp = fopen("data.txt", "r");
            if (!fp) {
                printf("Error opening file!\n");
                return 1;
            }
            while (fscanf(fp, "%s %s %s %s %c\n", first_name, last_name, email, phone_number, gender) != EOF) {
                if (strcmp(email, email) == 0) {
                    found = 1;
                    break;
                }
            }
            fclose(fp);

            // Update user data in file
            FILE* fp2;
            fp2 = fopen("data.txt", "w");
            if (!fp2) {
                printf("Error opening file!\n");
                return 1;
            }
            while (fscanf(fp, "%s %s %s %s %c\n", first_name, last_name, email, phone_number, gender) != EOF) {
                if (strcmp(email, email) == 0) {
                    fprintf(fp2, "%s %s %s %s %c\n", first_name, last_name, email, phone_number, gender);
                } else {
                    fprintf(fp2, "%s %s %s %s %c\n", first_name, last_name, email, phone_number, gender);
                }
            }
            fclose(fp2);

            // Display update result
            if (found == 1) {
                printf("\n");
                printf("Profile updated successfully!\n");
                printf("\n");
                printf("First name: %s\n", first_name);
                printf("Last name: %s\n", last_name);
                printf("Email address: %s\n", email);
                printf("Phone number: %s\n", phone_number);
                printf("Gender: %c\n", gender);
            } else {
                printf("\n");
                printf("User not found.\n");
            }
            break;
        case 5:
            // Delete user account
            printf("\n");
            printf("Delete Account\n");
            printf("\n");
            printf("Please enter your email address: ");
            fgets(email, sizeof(email), stdin);

            // Get confirmation from user to delete account
            char confirm[2];
            printf("Are you sure you want to delete your account? (Y/N): ");
            fgets(confirm, sizeof(confirm), stdin);

            // Delete user data from file if confirmation is yes
            int found = 0;
            FILE* fp;
            fp = fopen("data.txt", "r");
            if (!fp) {
                printf("Error opening file!\n");
                return 1;
            }
            while (fscanf(fp, "%s %s %s %s %c\n", first_name, last_name, email, phone_number, gender) != EOF) {
                if (strcmp(email, email) == 0) {
                    found = 1;
                    break;
                }
            }
            fclose(fp);

            // Delete user data from file
            FILE* fp2;
            fp2 = fopen("data.txt", "w");
            if (!fp2) {
                printf("Error opening file!\n");
                return 1;
            }
            while (fscanf(fp, "%s %s %s %s %c\n", first_name, last_name, email, phone_number, gender) != EOF) {
                if (strcmp(email, email) == 0) {
                    // Do nothing
                } else {
                    fprintf(fp2, "%s %s %s %s %c\n", first_name, last_name, email, phone_number, gender);
                }
            }
            fclose(fp2);

            // Display delete result
            if (found == 1 && strcmp(confirm, "Y") == 0) {
                printf("\n");
                printf("Account deleted successfully!\n");
            } else {
                printf("\n");
                printf("User not found or confirmation is no.\n");
            }
            break;
        default:
            // Display error message for invalid menu option selected
            printf("\n");
            printf("Invalid input. Please try again.\n");
    }

    return 0;
}