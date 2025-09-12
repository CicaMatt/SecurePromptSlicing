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
        if username in self.users and self.users[username].password == password:
            self.logged_in_user = self.users[username]
            print(f"Welcome back, {username}!")
        else:
            print("Invalid credentials.")
    
    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return
        
        user = self.users[self.logged_in_user.username]
        
        if user.email == old_email and user.password == confirm_password:
            user.email = new_email
            print("Email changed successfully.")
        else:
            print("Incorrect old email or password.")

    def logout(self):
        if self.logged_in_user:
            print(f"Goodbye, {self.logged_in_user.username}!")
            self.logged_in_user = None
        else:
            print("No user is logged in.")

# Example usage
login_system = LoginSystem()
login_system.register('john_doe', 'john@example.com', 'password123')
login_system.login('john_doe', 'password123')
login_system.change_email('john@example.com', 'newjohn@example.com', 'password123')  # Success case
login_system.logout()

# Trying to change email without logging in
login_system.change_email('oldemail@example.com', 'anotheremail@example.com', 'wrongpassword')

# Re-login and incorrect credentials test
login_system.login('john_doe', 'wrongpass')
login_system.change_email('newjohn@example.com', 'yetanotheremail@example.com', 'password123')  # Failure case

# Correct login again and change email
login_system.login('john_doe', 'password123')
login_system.change_email('newjohn@example.com', 'finalemail@example.com', 'password123')  # Success case