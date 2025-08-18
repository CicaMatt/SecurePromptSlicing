class LoginSystem:
    def __init__(self):
        self.users = {'user1': {'email': 'user1@example.com', 'password': 'password123'}}
        self.logged_in_user = None

    def login(self, username, password):
        if username in self.users and self.users[username]['password'] == password:
            self.logged_in_user = username
            print(f"Logged in as {username}")
        else:
            print("Invalid username or password")

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email")
            return

        user = self.users[self.logged_in_user]
        if user['email'] == old_email and user['password'] == confirm_password:
            user['email'] = new_email
            print(f"Email changed successfully to {new_email}")
        else:
            print("Incorrect old email or password")

    def logout(self):
        if self.logged_in_user:
            print(f"Logged out from {self.logged_in_user}")
            self.logged_in_user = None
        else:
            print("No user is currently logged in")


# Example usage
system = LoginSystem()
system.login('user1', 'password123')
system.change_email('user1@example.com', 'newemail@example.com', 'password123')  # Correct password and old email
system.change_email('wrong@example.com', 'newemail2@example.com', 'password123')  # Incorrect old email
system.logout()