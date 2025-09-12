import getpass

users = {
    'alice': {'password': '123456', 'email': 'alice@example.com'},
    'bob': {'password': 'abcdef', 'email': 'bob@example.com'}
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
        print("Email updated successfully.")
    else:
        print("Incorrect old email or password. Email not changed.")

def main():
    username = input("Username: ")
    password = getpass.getpass("Password: ")

    if login(username, password):
        change_email(username)
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()