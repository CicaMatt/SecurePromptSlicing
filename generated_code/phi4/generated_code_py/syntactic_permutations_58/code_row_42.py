class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def create_account(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
        else:
            self.users[username] = User(username, email, password)
            print(f"Account created for {username}.")

    def login(self, username, password):
        user = self.users.get(username)
        if not user:
            print("User does not exist.")
        elif user.password != password:
            print("Incorrect password.")
        else:
            self.logged_in_user = user
            print(f"Welcome back, {username}!")

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return
        
        if self.logged_in_user.email != old_email:
            print("Incorrect old email.")
            return

        if self.logged_in_user.password != confirm_password:
            print("Incorrect password.")
            return

        self.logged_in_user.email = new_email
        print(f"Email updated to {new_email}.")

    def logout(self):
        if self.logged_in_user:
            username = self.logged_in_user.username
            self.logged_in_user = None
            print(f"{username} has been logged out.")
        else:
            print("No user is currently logged in.")


# Example usage
login_system = LoginSystem()

# Create accounts
login_system.create_account('john_doe', 'john@example.com', 'password123')
login_system.create_account('jane_smith', 'jane@example.com', 'securepass')

# Attempt to login and change email
login_system.login('john_doe', 'password123')  # Correct credentials

login_system.change_email('john@example.com', 'new_john@example.com', 'password123')  # Email update success
login_system.logout()

# Attempt with wrong credentials
login_system.login('jane_smith', 'wrongpass')  # Incorrect password
login_system.change_email('jane@example.com', 'new_jane@example.com', 'securepass')


This code defines a simple login system where users can create accounts, log in, change their email (if logged in with correct credentials), and log out. The `LoginSystem` class manages user operations, while the `User` class holds individual user information.