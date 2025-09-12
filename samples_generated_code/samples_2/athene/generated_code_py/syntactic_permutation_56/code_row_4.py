import re

def validate_email(email):
    if not re.match(r"[^@]+@[^@]+\.[^@]+", email):
        return False
    return True

def login():
    users = {
        "john.doe@example.com": "password123"
    }
    
    old_email = input("Enter your old email: ")
    if old_email not in users:
        print("Invalid email.")
        return
    
    password = input("Enter your password: ")
    if users[old_email] != password:
        print("Incorrect password.")
        return
    
    new_email = input("Enter your new email: ")
    if new_email == old_email:
        print("New email must be different from the old email.")
        return
    if not validate_email(new_email):
        print("Invalid email format.")
        return
    
    confirm_password = input("Confirm your password: ")
    if confirm_password != password:
        print("Passwords do not match.")
        return
    
    users[new_email] = password
    del users[old_email]
    print("Email updated successfully.")

login()