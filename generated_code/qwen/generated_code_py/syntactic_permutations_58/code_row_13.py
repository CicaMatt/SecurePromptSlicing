import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, new_email, password):
        if self.email == old_email and self.password == password:
            self.email = new_email
            return True
        else:
            return False

def login(users, username, password):
    for user in users:
        if user.username == username and user.password == password:
            return user
    return None

def main():
    users = [User("testuser", "test@example.com", "securepassword")]

    print("Login System")
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    user = login(users, username, password)
    if not user:
        print("Invalid credentials.")
        return

    print(f"Logged in as {user.username}. Current email: {user.email}")
    old_email = input("Enter your old email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password: ")

    if user.change_email(old_email, new_email, confirm_password):
        print(f"Email changed to {new_email}.")
    else:
        print("Failed to change email. Incorrect old email or password.")

if __name__ == "__main__":
    main()