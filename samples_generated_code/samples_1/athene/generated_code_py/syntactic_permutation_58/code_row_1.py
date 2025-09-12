import getpass

users = {
    'alice': {'email': 'alice@example.com', 'password': 'alice123'},
    'bob': {'email': 'bob@example.com', 'password': 'bob456'}
}

def login(username, password):
    if username in users and users[username]['password'] == password:
        return True
    return False

def change_email(username, old_email, password, new_email):
    if not login(username, password):
        print("Login failed")
        return
    if users[username]['email'] != old_email:
        print("Incorrect old email")
        return
    users[username]['email'] = new_email
    print("Email changed successfully")

def main():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    
    if not login(username, password):
        print("Invalid credentials")
        return
    
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    change_email(username, old_email, password, new_email)

if __name__ == "__main__":
    main()