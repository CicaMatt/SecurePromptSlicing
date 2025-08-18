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
            print(f"User {username} registered successfully.")

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.password == password:
            self.logged_in_user = user
            print(f"User {username} logged in.")
        else:
            print("Invalid username or password.")

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return

        if self.logged_in_user.email != old_email or self.logged_in_user.password != confirm_password:
            print("Invalid old email or password.")
            return

        self.logged_in_user.email = new_email
        print(f"Email changed successfully to {new_email}.")

    def logout(self):
        if self.logged_in_user:
            print(f"User {self.logged_in_user.username} logged out.")
            self.logged_in_user = None
        else:
            print("No user is currently logged in.")


# Example usage:
system = LoginSystem()
system.register('john_doe', 'john@example.com', 'password123')
system.login('john_doe', 'password123')

# Change email with correct credentials
system.change_email('john@example.com', 'john_new@example.com', 'password123')

# Attempt to change email with wrong password
system.change_email('john_new@example.com', 'wrong@example.com', 'wrong_password')

# Logout and try to change email without being logged in
system.logout()
system.change_email('john_new@example.com', 'another_email@example.com', 'password123')