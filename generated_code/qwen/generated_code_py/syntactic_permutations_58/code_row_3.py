import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = hashlib.sha256(password.encode()).hexdigest()
        self.logged_in = False

    def login(self, password):
        if hashlib.sha256(password.encode()).hexdigest() == self.password_hash:
            self.logged_in = True
            return True
        else:
            self.logged_in = False
            return False

    def change_email(self, old_email, new_email, password):
        if not self.logged_in:
            return "You must be logged in to change your email."
        if self.email != old_email:
            return "The old email you entered is incorrect."
        if not self.login(password):
            return "The password you entered is incorrect."
        self.email = new_email
        return "Email changed successfully."

# Example usage
user = User("john_doe", "old_email@example.com", "securepassword")

# Simulate login
login_status = user.login("securepassword")
print("Login successful" if login_status else "Login failed")

# Attempt to change email
result = user.change_email("old_email@example.com", "new_email@example.com", "securepassword")
print(result)

# Check if email changed
print(f"Updated email: {user.email}")