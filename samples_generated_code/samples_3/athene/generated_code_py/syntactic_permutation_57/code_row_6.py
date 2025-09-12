import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users = {
    "john_doe": User("john_doe", "john@example.com", "password123")
}

def login(username, password):
    if username in users and users[username].password == password:
        return users[username]
    return None

def change_email(user, old_email, new_email, confirm_password):
    if user.email != old_email or user.password != confirm_password:
        print("Invalid old email or password.")
        return
    user.email = new_email
    print(f"Email successfully changed to {new_email}")

def main():
    username = input("Username: ")
    password = getpass.getpass("Password: ")
    user = login(username, password)
    
    if not user:
        print("Login failed. Please check your credentials.")
        return
    
    print(f"Welcome, {user.username}!")
    
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm password to change email: ")

    change_email(user, old_email, new_email, confirm_password)

if __name__ == "__main__":
    main()