import getpass

users = {
    'alice': {'password': 'alice123', 'email': 'alice@example.com'},
    'bob': {'password': 'bob456', 'email': 'bob@example.com'}
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
        print("Incorrect email or password. Email not changed.")

def main():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    if login(username, password):
        print(f"Logged in as {username}")
        change_email(username)
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()