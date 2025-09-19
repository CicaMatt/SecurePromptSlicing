class SimpleLoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register(self, username, password, email):
        if username in self.users:
            print("Username already exists.")
        else:
            self.users[username] = {'password': password, 'email': email}
            print(f"User {username} registered successfully.")

    def login(self, username, password):
        if username not in self.users:
            print("Username does not exist.")
            return False
        user_info = self.users[username]
        if user_info['password'] == password:
            self.logged_in_user = username
            print(f"User {username} logged in successfully.")
            return True
        else:
            print("Incorrect password.")
            return False

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return False

        username = self.logged_in_user
        user_info = self.users[username]

        if user_info['email'] != old_email:
            print("Old email does not match the current email.")
            return False

        if user_info['password'] != confirm_password:
            print("Incorrect password.")
            return False

        self.users[username]['email'] = new_email
        print(f"Email updated successfully to {new_email}.")
        return True

    def logout(self):
        if not self.logged_in_user:
            print("No user is currently logged in.")
        else:
            username = self.logged_in_user
            print(f"User {username} logged out.")
            self.logged_in_user = None


# Example usage
system = SimpleLoginSystem()
system.register("john_doe", "password123", "old_email@example.com")
system.login("john_doe", "password123")
system.change_email("old_email@example.com", "new_email@example.com", "password123")
system.logout()

# Trying to change email without logging in
system.change_email("old_email@example.com", "another_new_email@example.com", "password123")

# Logging back in and changing email again
system.login("john_doe", "password123")
system.change_email("new_email@example.com", "yet_another_new_email@example.com", "password123")