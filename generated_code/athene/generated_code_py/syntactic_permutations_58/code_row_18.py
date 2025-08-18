import getpass

users = {
    'john': {
        'password': '12345',
        'email': 'john@example.com'
    }
}

def change_email(username):
    if username not in users:
        print("User does not exist.")
        return
    
    old_email = input("Enter your current email: ")
    password = getpass.getpass("Enter your password: ")

    user_info = users[username]
    
    if old_email == user_info['email'] and password == user_info['password']:
        new_email = input("Enter your new email: ")
        user_info['email'] = new_email
        print("Email updated successfully.")
    else:
        print("Incorrect email or password. Email not changed.")

username = input("Enter your username: ")
change_email(username)