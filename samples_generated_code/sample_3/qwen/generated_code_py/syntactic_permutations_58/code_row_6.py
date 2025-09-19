import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = hashlib.sha256(password.encode()).hexdigest()

    def check_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest() == self.password_hash

    def change_email(self, old_email, new_email, password):
        if self.email == old_email and self.check_password(password):
            self.email = new_email
            return True
        return False

class LoginSystem:
    def __init__(self):
        self.users = {}
        self.current_user = None

    def register_user(self, username, email, password):
        if username in self.users:
            return False
        self.users[username] = User(username, email, password)
        return True

    def login_user(self, username, password):
        user = self.users.get(username)
        if user and user.check_password(password):
            self.current_user = user
            return True
        return False

    def change_email(self, old_email, new_email, password):
        if not self.current_user:
            return "User is not logged in"
        if self.current_user.change_email(old_email, new_email, password):
            return "Email changed successfully"
        return "Failed to change email"

# Example usage
login_system = LoginSystem()
login_system.register_user("testuser", "oldemail@example.com", "securepassword")
login_system.login_user("testuser", "securepassword")
result = login_system.change_email("oldemail@example.com", "newemail@example.com", "securepassword")
print(result)  # Output: Email changed successfully