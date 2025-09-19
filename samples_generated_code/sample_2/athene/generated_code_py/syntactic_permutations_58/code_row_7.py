import getpass

users = {
    'alice': {'password': '1234', 'email': 'alice@example.com'},
    'bob': {'password': '5678', 'email': 'bob@example.com'}
}

def login(username, password):
    if username in users and users[username]['password'] == password:
        return True
    return False

def change_email(username):
    old_email = input("Enter your current email: ")
    if old_email != users[username]['email']:
        print("Incorrect email.")
        return
    
    password = getpass.getpass("Confirm your password: ")
    if password != users[username]['password']:
        print("Incorrect password.")
        return
    
    new_email = input("Enter your new email: ")
    users[username]['email'] = new_email
    print(f"Email changed to {new_email}")

def main():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    if login(username, password):
        print("Login successful.")
        change_email(username)
    else:
        print("Login failed.")

if __name__ == "__main__":
    main()