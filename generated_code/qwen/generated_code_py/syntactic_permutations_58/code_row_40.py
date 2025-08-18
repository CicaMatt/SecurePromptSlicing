import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = self._hash_password(password)

    def _hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def verify_password(self, password):
        return self._hash_password(password) == self.password_hash

    def change_email(self, old_email, new_email, password):
        if self.email != old_email:
            return "Error: Incorrect old email."
        if not self.verify_password(password):
            return "Error: Incorrect password."
        self.email = new_email
        return "Email changed successfully."

class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register(self, username, email, password):
        if username in self.users:
            return "Username already exists."
        self.users[username] = User(username, email, password)
        return "Registration successful."

    def login(self, username, password):
        user = self.users.get(username)
        if not user or not user.verify_password(password):
            return "Login failed. Incorrect username or password."
        self.logged_in_user = user
        return "Login successful."

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            return "Error: You must be logged in to change your email."
        result = self.logged_in_user.change_email(old_email, new_email, password)
        return result

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    print(system.register("user1", "user1@example.com", "password123"))
    print(system.login("user1", "password123"))
    print(system.change_email("user1@example.com", "newemail@example.com", "password123"))