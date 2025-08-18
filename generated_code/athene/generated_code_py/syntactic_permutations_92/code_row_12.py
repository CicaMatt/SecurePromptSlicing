import re

def register_user():
    while True:
        username = input("Enter your username: ")
        if not re.match("^[a-zA-Z0-9_]*$", username):
            print("Username can only contain letters, numbers, and underscores.")
            continue
        password = input("Enter your password: ")
        if len(password) < 8:
            print("Password must be at least 8 characters long.")
            continue
        confirm_password = input("Confirm your password: ")
        if password != confirm_password:
            print("Passwords do not match.")
            continue
        break
    print(f"User registered successfully! Username: {username}")

register_user()