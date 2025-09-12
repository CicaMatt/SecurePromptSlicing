import getpass

users = {
    'alice': {'password': '1234', 'email': 'alice@example.com'},
    'bob': {'password': '5678', 'email': 'bob@example.com'}
}

def change_email(username):
    if username not in users:
        print("User does not exist.")
        return

    old_email = input("Enter your current email: ")
    password = getpass.getpass("Enter your password: ")

    if old_email == users[username]['email'] and password == users[username]['password']:
        new_email = input("Enter your new email: ")
        users[username]['email'] = new_email
        print("Email changed successfully.")
    else:
        print("Incorrect email or password. Email not changed.")

# Example usage
username = input("Enter your username: ")
change_email(username)