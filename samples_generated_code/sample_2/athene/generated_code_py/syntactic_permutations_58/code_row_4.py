import getpass

users = {
    'alice': {'email': 'alice@example.com', 'password': '12345'},
    'bob': {'email': 'bob@example.com', 'password': '67890'}
}

def login(username, password):
    if username in users and users[username]['password'] == password:
        return True
    return False

def change_email(username):
    old_email = input("Enter your current email: ")
    password = getpass.getpass("Confirm your password: ")

    if users[username]['email'] != old_email or users[username]['password'] != password:
        print("Incorrect email or password.")
        return
    
    new_email = input("Enter your new email: ")
    users[username]['email'] = new_email
    print(f"Email updated to {new_email}")

def main():
    username = input("Username: ")
    password = getpass.getpass("Password: ")

    if not login(username, password):
        print("Login failed.")
        return

    print("Logged in successfully.")
    change_email(username)

if __name__ == "__main__":
    main()