import os
import hashlib

def register():
    # Get user input for user name, password, first name, last name and email
    username = input("Enter a username: ")
    password = input("Enter a password: ")
    f_name = input("Enter your first name: ")
    l_name = input("Enter your last name: ")
    email = input("Enter your email: ")

    # Hash the user's password
    hashed_password = hashlib.sha256(password).hexdigest()

    # Check if username already exists in database
    if os.path.exists(username):
        return "Username exists!"
    else:
        # Insert new user into database
        db = open("database.txt", 'a')
        db.write(username + "\n")
        db.close()

        # Return success message
        return "Registration succeeded!"

# Test the register function
print(register())