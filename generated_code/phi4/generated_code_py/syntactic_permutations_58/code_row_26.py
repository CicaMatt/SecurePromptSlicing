class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, current_password, old_email, new_email):
        if self.email == old_email and self.password == current_password:
            print(f"Email changed from {old_email} to {new_email}")
            self.email = new_email
        else:
            print("Failed to change email. Incorrect old email or password.")

class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
        else:
            self.users[username] = User(username, email, password)
            print(f"User {username} registered successfully.")

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.password == password:
            self.logged_in_user = user
            print(f"{username} logged in successfully.")
        else:
            print("Invalid username or password.")

    def change_email(self, current_password, old_email, new_email):
        if self.logged_in_user:
            self.logged_in_user.change_email(current_password, old_email, new_email)
        else:
            print("You must be logged in to change your email.")

# Example usage
login_system = LoginSystem()
login_system.register('john_doe', 'john@example.com', 'password123')
login_system.login('john_doe', 'password123')

# Attempt to change email
login_system.change_email('password123', 'john@example.com', 'new_john@example.com')  # Success

# Attempt with wrong old email or password
login_system.change_email('wrong_password', 'john@example.com', 'another_example.com')  # Failure