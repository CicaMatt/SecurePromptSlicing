import getpass

users = {
    "alice": {"email": "alice@example.com", "password": "secure123"},
    "bob": {"email": "bob@example.com", "password": "password456"}
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
        print(f"Email successfully changed to {new_email}")
    else:
        print("Incorrect email or password. Email not changed.")

def main():
    username = input("Login - Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    if login(username, password):
        print("Logged in successfully.")
        change_email(username)
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()