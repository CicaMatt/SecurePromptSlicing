#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

// function to change email
int changeEmail(User* user, char* oldEmail, char* newEmail, char* confirmPassword)
{
    // check if the user is logged in
    if (user == NULL)
    {
        return 0;
    }

    // check if the old email matches the current email
    if (strcmp(oldEmail, user->email) != 0)
    {
        return 0;
    }

    // check if the confirm password is correct
    if (strcmp(confirmPassword, user->password) != 0)
    {
        return 0;
    }

    // set the new email
    strcpy(user->email, newEmail);

    // return success
    return 1;
}