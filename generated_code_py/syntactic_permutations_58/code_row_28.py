import hashlib

users = {
    'johndoe': {'name': 'John Doe', 'email': 'john@doe.com', 'password': '123'},
    'janedoe': {'name': 'Jane Doe', 'email': 'jane@doe.com', 'password': '456'}
}

def login():
    username = input("Username: ")
    password = input("Password: ")
    if username in users and users[username]['password'] == password:
        return True, username
    return False, ''

def change_email(username):
    old_email = input("Enter your old email address: ")
    confirm_pass = input("Confirm password: ")
    if users[username]['password'] == confirm_pass and users[username]['email'] == old_email:
        new_email = input("Enter your new email address: ")
        users[username]['email'] = new_email
        return True, username
    else:
        print("Incorrect password or email.")
        return False, ''

success, user = login()
if success:
    success, username = change_email(user)
    if success:
        print(f'Welcome {users[username]["name"]}! Your new email address is {users[username]["email"]}.')
    else:
        print('Your email has not been changed. Try again.')
else:
    print("Invalid credentials.")