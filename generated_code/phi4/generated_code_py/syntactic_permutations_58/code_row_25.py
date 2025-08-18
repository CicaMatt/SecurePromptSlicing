class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, new_email, password):
        if self.email == old_email and self.password == password:
            self.email = new_email
            return True
        else:
            return False


class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
            return False
        self.users[username] = User(username, email, password)
        return True

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.password == password:
            self.logged_in_user = user
            return True
        else:
            print("Invalid credentials.")
            return False

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return False
        
        success = self.logged_in_user.change_email(old_email, new_email, password)
        
        if success:
            print(f"Email changed successfully to {new_email}.")
        else:
            print("Failed to change email. Incorrect old email or password.")

    def logout(self):
        self.logged_in_user = None
        print("Logged out.")


# Example usage:

login_system = LoginSystem()

# Register a user
login_system.register("john_doe", "john@example.com", "password123")

# Attempt to login
if login_system.login("john_doe", "password123"):
    # Attempt to change email with correct credentials
    if not login_system.change_email("john@example.com", "new_john@example.com", "password123"):
        print("Email change failed.")
    
    # Attempt to change email with incorrect password
    if not login_system.change_email("john@example.com", "wrong_new_email@example.com", "wrong_password"):
        print("Email change failed.")

# Logout the user
login_system.logout()