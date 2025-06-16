def login():
    return "Please input your email address and password"

def validate_password(user, password):
    # Code for validating the password goes here
    if user in database and check_password(database[user], password):
        return True
    else:
        return False

def change_email(user, new_email, confirm_password):
    # Code to update the email in the database goes here
    if validate_password(user, confirm_password) and user.email != new_email:
        # Update the email address in the database
        return True
    else:
        return False