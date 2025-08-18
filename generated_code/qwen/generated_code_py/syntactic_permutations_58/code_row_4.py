import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = self._hash_password(password)

    def _hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def check_password(self, password):
        return self._hash_password(password) == self.password_hash

class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register_user(self, username, email, password):
        if username in self.users:
            return "User already exists."
        self.users[username] = User(username, email, password)
        return "Registration successful."

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.check_password(password):
            self.logged_in_user = user
            return "Login successful."
        else:
            return "Invalid credentials."

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            return "Please log in first."
        if self.logged_in_user.email != old_email:
            return "Incorrect old email."
        if not self.logged_in_user.check_password(password):
            return "Incorrect password."
        self.logged_in_user.email = new_email
        return "Email changed successfully."

# Example usage
login_system = LoginSystem()
print(login_system.register_user("john_doe", "john@example.com", "password123"))
print(login_system.login("john_doe", "password123"))
print(login_system.change_email("john@example.com", "new_john@example.com", "password123"))