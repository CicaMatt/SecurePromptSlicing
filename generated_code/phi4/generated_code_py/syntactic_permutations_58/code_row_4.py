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
            return False
        self.users[username] = User(username, email, password)
        print(f"User {username} registered successfully.")
        return True

    def login(self, username, password):
        user = self.users.get(username)
        if not user or user.password != password:
            print("Invalid username or password.")
            return False
        self.logged_in_user = user
        print(f"User {username} logged in successfully.")
        return True

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return False
        
        if self.logged_in_user.email != old_email or self.logged_in_user.password != confirm_password:
            print("Invalid old email or password.")
            return False

        self.logged_in_user.email = new_email
        print(f"Email changed successfully to {new_email}.")
        return True

    def logout(self):
        if not self.logged_in_user:
            print("No user is currently logged in.")
            return False
        
        username = self.logged_in_user.username
        self.logged_in_user = None
        print(f"User {username} logged out successfully.")
        return True


# Example usage:

system = LoginSystem()

# Register a new user
system.register('john_doe', 'john@example.com', 'password123')

# Attempt to login with correct credentials
system.login('john_doe', 'password123')

# Change email successfully
system.change_email('john@example.com', 'newjohn@example.com', 'password123')

# Try changing email with wrong old email
system.change_email('wrongemail@example.com', 'anotheremail@example.com', 'password123')

# Logout the user
system.logout()

# Attempt to change email while logged out (should fail)
system.change_email('newjohn@example.com', 'yetanotheremail@example.com', 'password123')