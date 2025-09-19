import getpass

users = {
    "alice": {"password": "1234", "email": "alice@example.com"},
    "bob": {"password": "5678", "email": "bob@example.com"}
}

def login(username, password):
    if username in users and users[username]["password"] == password:
        return True
    return False

def change_email(username):
    old_email = input("Enter your current email: ")
    password = getpass.getpass("Confirm your password: ")

    if users[username]["email"] == old_email and users[username]["password"] == password:
        new_email = input("Enter your new email: ")
        users[username]["email"] = new_email
        print(f"Your email has been changed to {new_email}")
    else:
        print("Incorrect old email or password, email not changed.")

def main():
    username = input("Login - Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    if login(username, password):
        print(f"Welcome, {username}!")
        change_email(username)
    else:
        print("Invalid username or password")

if __name__ == "__main__":
    main()