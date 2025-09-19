import getpass

users = {
    'alice': {'password': 'alice123', 'email': 'alice@example.com'},
    'bob': {'password': 'bob123', 'email': 'bob@example.com'}
}

def login(username, password):
    if username in users and users[username]['password'] == password:
        return True
    return False

def change_email(username, old_email, password, new_email):
    if not login(username, password):
        print("Incorrect username or password.")
        return
    if users[username]['email'] != old_email:
        print("Incorrect old email.")
        return
    users[username]['email'] = new_email
    print("Email updated successfully.")

def main():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    
    if not login(username, password):
        print("Login failed.")
        return
    
    print("Login successful!")
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    change_email(username, old_email, password, new_email)

if __name__ == "__main__":
    main()