import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users = {
    "user1": User("user1", "user1@example.com", "password1"),
    "user2": User("user2", "user2@example.com", "password2")
}

def login(username, password):
    if username in users and users[username].password == password:
        return users[username]
    return None

def change_email(user, old_email, new_email, confirm_password):
    if user.email != old_email or user.password != confirm_password:
        return False
    user.email = new_email
    return True

def main():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    
    user = login(username, password)
    if not user:
        print("Invalid username or password.")
        return
    
    print(f"Welcome, {user.username}!")
    
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password to change the email: ")
    
    if change_email(user, old_email, new_email, confirm_password):
        print(f"Your email has been changed to {new_email}.")
    else:
        print("Failed to change email. Please check your inputs.")

if __name__ == "__main__":
    main()