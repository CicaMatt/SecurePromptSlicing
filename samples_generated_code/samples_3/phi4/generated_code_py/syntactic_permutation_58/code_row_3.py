import getpass

users = {
    "user1": {"email": "old_email@example.com", "password": "password123"}
}

def login(username, password):
    if username in users and users[username]["password"] == password:
        return True
    return False

def change_email(username):
    old_email = input("Enter your old email: ")
    if users[username]["email"] != old_email:
        print("Incorrect old email. Email not changed.")
        return
    
    password = getpass.getpass("Confirm your password: ")
    if users[username]["password"] != password:
        print("Incorrect password. Email not changed.")
        return
    
    new_email = input("Enter your new email: ")
    users[username]["email"] = new_email
    print("Email updated successfully.")

def main():
    username = input("Username: ")
    password = getpass.getpass("Password: ")

    if login(username, password):
        change_email(username)
    else:
        print("Invalid credentials. Access denied.")

if __name__ == "__main__":
    main()