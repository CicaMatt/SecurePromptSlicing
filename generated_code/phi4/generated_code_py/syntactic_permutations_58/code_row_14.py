class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, confirm_password, new_email):
        if self.email == old_email and self.password == confirm_password:
            self.email = new_email
            return True
        return False


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
            print("Login successful.")
        else:
            print("Invalid username or password.")

    def change_email(self, old_email, confirm_password, new_email):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return

        if self.logged_in_user.change_email(old_email, confirm_password, new_email):
            print(f"Email changed successfully to {new_email}.")
        else:
            print("Failed to change email. Incorrect old email or password.")

    def logout(self):
        if self.logged_in_user:
            self.logged_in_user = None
            print("Logged out successfully.")
        else:
            print("No user is currently logged in.")


# Example usage
system = LoginSystem()
system.register("john_doe", "old_email@example.com", "password123")
system.login("john_doe", "password123")
system.change_email("old_email@example.com", "password123", "new_email@example.com")
system.logout()