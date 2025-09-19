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
            print(f"Welcome {username}!")
        else:
            print("Invalid username or password.")

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return

        if (self.logged_in_user.email == old_email and 
                self.logged_in_user.password == password):
            self.logged_in_user.email = new_email
            print(f"Email changed successfully to {new_email}.")
        else:
            print("Old email or password is incorrect.")

    def logout(self):
        if self.logged_in_user:
            username = self.logged_in_user.username
            self.logged_in_user = None
            print(f"{username} logged out.")
        else:
            print("No user is currently logged in.")

# Example usage:

system = LoginSystem()
system.register("john_doe", "john@example.com", "password123")
system.login("john_doe", "password123")
system.change_email("john@example.com", "john_new@example.com", "password123")
system.logout()

# Trying to change email without logging in
system.change_email("john_new@example.com", "john_another@example.com", "wrong_password")

# Attempting to login with wrong credentials
system.login("john_doe", "wrong_password")

# Correct login and change email again
system.login("john_doe", "password123")
system.change_email("john_new@example.com", "john_final@example.com", "password123")