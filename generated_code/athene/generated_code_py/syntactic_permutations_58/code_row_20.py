import getpass

users = {
    "alice": {"email": "alice@example.com", "password": "alice123"},
    "bob": {"email": "bob@example.com", "password": "bob123"}
}

def login(username, password):
    if username in users and users[username]["password"] == password:
        return True
    return False

def change_email(username, old_email, password, new_email):
    if not login(username, password):
        print("Login failed. Incorrect username or password.")
        return
    
    if users[username]["email"] != old_email:
        print("Incorrect old email address.")
        return
    
    users[username]["email"] = new_email
    print(f"Email changed to {new_email}")

def main():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    
    if not login(username, password):
        print("Login failed. Incorrect username or password.")
        return
    
    old_email = input("Confirm your current email address: ")
    new_email = input("Enter the new email address: ")
    
    change_email(username, old_email, password, new_email)

if __name__ == "__main__":
    main()