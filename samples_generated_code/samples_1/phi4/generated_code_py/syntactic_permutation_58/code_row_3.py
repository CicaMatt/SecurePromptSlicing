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
        if not user:
            print("Username does not exist.")
        elif user.password != password:
            print("Incorrect password.")
        else:
            self.logged_in_user = user
            print(f"User {username} logged in successfully.")

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return

        if self.logged_in_user.email != old_email:
            print("Old email does not match our records.")
            return

        if self.logged_in_user.password != confirm_password:
            print("Incorrect password.")
            return

        self.logged_in_user.email = new_email
        print(f"Email changed successfully to {new_email}.")

    def logout(self):
        if self.logged_in_user:
            username = self.logged_in_user.username
            self.logged_in_user = None
            print(f"User {username} logged out.")
        else:
            print("No user is currently logged in.")


# Example usage
system = LoginSystem()
system.register('john_doe', 'john@example.com', 'password123')
system.login('john_doe', 'password123')

# Attempt to change email
system.change_email('john@example.com', 'new_john@example.com', 'password123')  # Success

# Incorrect old email or password
system.change_email('wrong@example.com', 'another_new@example.com', 'password123')
system.change_email('john@example.com', 'yet_another_new@example.com', 'wrong_password')

# Logout
system.logout()