#include <stdio.h> // for IO
#include <string.h>
#include <stdlib.h>
#define MAX_EMAIL 100 // maximum length of email
#define MAX_PWD 50    // maximum length of password
struct user {
char name[50];         
char email[MAX_EMAIL];       
char pwd[MAX_PWD];    
};

int main() {
// Create a database of users
struct user db[] = {{"alice", "alice@example.com", "pass1"},
                     {"bob", "bob@example.com", "pass2"}};
// Initialize the number of users in the database
int n_users = sizeof(db) / sizeof(struct user);
// Display login menu
printf("Welcome to the email update service!\n");
printf("Please enter your old email: ");
char old_email[MAX_EMAIL]; // input box for old email
scanf("%99s", old_email);  // read old email from user
// Find user in database by old email
int idx = -1;
for (int i = 0; i < n_users; i++) {
if (strcmp(old_email, db[i].email) == 0) {
idx = i;
break;
}
}
// If user not found, display error
if (idx == -1) {
printf("User not found!\n");
return 1;
}
// Display password prompt
printf("Please enter your confirmation password: ");
char pwd[MAX_PWD]; // input box for password
scanf("%49s", pwd); // read password from user
// If password is incorrect, display error
if (strcmp(pwd, db[idx].pwd) != 0) {
printf("Incorrect password!\n");
return 1;
}
// Display new email prompt
printf("Please enter your new email: ");
char new_email[MAX_EMAIL]; // input box for new email
scanf("%99s", new_email);  // read new email from user
// If new email is already in use, display error
for (int i = 0; i < n_users; i++) {
if (strcmp(new_email, db[i].email) == 0 && i != idx) {
printf("Email already in use!\n");
return 1;
}
}
// Update user email
db[idx].email = new_email;
printf("Email updated successfully!\n");
return 0;
}

### Explanation:
The code first includes the necessary libraries for input and output as well as string manipulation. It then defines a structure to store user information including name, email, and password. The main function starts by creating a database of users, in this case, Alice and Bob with their respective emails and passwords. It then prompts the user to enter their old email, reads it from stdin, and finds the corresponding user in the database using a for loop and strcmp. If no matching email is found or if the password entered by the user does not match the one associated with the email, an error message is displayed and the program exits with status code 1.

Once the correct user is identified, the program prompts the user to enter their new email, reads it from stdin, and checks if the email already exists in the database using another for loop and strcmp. If a matching email is found, an error message is displayed and the program exits with status code 1.

Finally, if both emails are valid, the program updates the user's email in the database and displays a success message before exiting with status code 0.