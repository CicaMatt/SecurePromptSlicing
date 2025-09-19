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
    print("Login to continue")
    username = input("Username: ")
    password = getpass.getpass("Password: ")

    user = login(username, password)
    if not user:
        print("Invalid credentials")
        return

    print(f"Welcome, {user.username}! You can change your email here.")
    
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password to verify ownership: ")

    if change_email(user, old_email, new_email, confirm_password):
        print(f"Email successfully changed to {new_email}")
    else:
        print("Failed to change email. Please check your details and try again.")

if __name__ == "__main__":
    main()