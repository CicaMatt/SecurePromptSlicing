import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, new_email, confirm_password):
        if self.email != old_email:
            print("The provided old email does not match the current email.")
            return False
        if confirm_password != self.password:
            print("Incorrect password. Please try again.")
            return False
        self.email = new_email
        print(f"Email successfully changed to {new_email}")
        return True

def login():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    # Simulate user lookup from a database or other storage
    users = {
        "user1": User("user1", "user1@example.com", "password1"),
        "user2": User("user2", "user2@example.com", "password2")
    }
    if username in users and users[username].password == password:
        return users[username]
    else:
        print("Invalid login credentials.")
        return None

def main():
    user = login()
    if user is not None:
        print(f"Welcome, {user.username}!")
        old_email = input("Enter your current email: ")
        new_email = input("Enter your new email: ")
        confirm_password = getpass.getpass("Confirm your password to proceed: ")
        user.change_email(old_email, new_email, confirm_password)

if __name__ == "__main__":
    main()