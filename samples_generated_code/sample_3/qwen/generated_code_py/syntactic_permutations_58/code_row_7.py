from getpass import getpass

# Simulated database of users
users = {
    "john_doe": {"password": "securepassword123", "email": "john@example.com"}
}

def login():
    username = input("Enter your username: ")
    password = getpass("Enter your password: ")

    if username in users and users[username]["password"] == password:
        print("Login successful.")
        return username
    else:
        print("Invalid username or password.")
        return None

def change_email(username):
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")

    if users[username]["email"] == old_email:
        confirm_password = getpass("Confirm your password: ")
        if users[username]["password"] == confirm_password:
            users[username]["email"] = new_email
            print("Email changed successfully.")
        else:
            print("Password confirmation failed. Email not changed.")
    else:
        print("Old email does not match. Email not changed.")

def main():
    username = login()
    if username:
        change_email(username)

if __name__ == "__main__":
    main()