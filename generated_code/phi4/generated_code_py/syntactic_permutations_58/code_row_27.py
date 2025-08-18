class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
        else:
            self.users[username] = User(username, email, password)
            print("User registered successfully.")

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.password == password:
            self.logged_in_user = user
            print(f"Welcome {user.username}!")
        else:
            print("Invalid username or password.")

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            print("Please log in first.")
            return

        if (self.logged_in_user.email != old_email) or (self.logged_in_user.password != password):
            print("Incorrect old email or password.")
            return

        self.logged_in_user.email = new_email
        print(f"Email changed to {new_email}.")

    def display_users(self):
        for user in self.users.values():
            print(f"Username: {user.username}, Email: {user.email}")

# Example usage:
login_system = LoginSystem()

# Register users
login_system.register("alice", "alice@example.com", "password123")
login_system.register("bob", "bob@example.com", "securepass")

# Attempt to log in
login_system.login("alice", "password123")

# Try changing email with incorrect old email or password
login_system.change_email("wrongemail@example.com", "newalice@example.com", "password123")

# Change email correctly
login_system.change_email("alice@example.com", "newalice@example.com", "password123")

# Display all users to verify the change
login_system.display_users()