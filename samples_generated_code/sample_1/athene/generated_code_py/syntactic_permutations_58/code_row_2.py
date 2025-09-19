import getpass

users = {
    "user1": {"email": "user1@example.com", "password": "pass1"},
    "user2": {"email": "user2@example.com", "password": "pass2"}
}

def login(username, password):
    if username in users and users[username]['password'] == password:
        return True
    return False

def change_email(username):
    old_email = input("Enter your current email: ")
    password = getpass.getpass("Confirm your password: ")

    if users[username]['email'] == old_email and users[username]['password'] == password:
        new_email = input("Enter your new email: ")
        users[username]['email'] = new_email
        print("Email changed successfully.")
    else:
        print("Incorrect email or password.")

def main():
    username = input("Username: ")
    password = getpass.getpass("Password: ")

    if login(username, password):
        print("Logged in successfully.")
        change_email(username)
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()