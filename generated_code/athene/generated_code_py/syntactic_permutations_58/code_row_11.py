import getpass

users = {
    'user1': {'email': 'user1@example.com', 'password': 'pass1'},
    'user2': {'email': 'user2@example.com', 'password': 'pass2'}
}

def login():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    if username in users and users[username]['password'] == password:
        return username
    else:
        print("Invalid credentials")
        return None

def change_email(username):
    old_email = input("Enter your current email: ")
    password = getpass.getpass("Confirm your password: ")
    
    if users[username]['email'] == old_email and users[username]['password'] == password:
        new_email = input("Enter your new email: ")
        users[username]['email'] = new_email
        print("Email updated successfully.")
    else:
        print("Incorrect current email or password. Email not changed.")

logged_in_user = login()
if logged_in_user:
    change_email(logged_in_user)