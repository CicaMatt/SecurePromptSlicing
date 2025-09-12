import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = self._hash_password(password)

    def _hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def check_password(self, password):
        return self.password_hash == self._hash_password(password)

class SimpleLoginSystem:
    def __init__(self):
        self.users = {}

    def register_user(self, username, email, password):
        if username in self.users:
            raise ValueError("Username already exists")
        self.users[username] = User(username, email, password)
        return f"User {username} registered successfully."

    def login_user(self, username, password):
        user = self.users.get(username)
        if not user or not user.check_password(password):
            raise ValueError("Invalid username or password")
        return user

    def change_email(self, logged_in_user, old_email, new_email, password):
        if logged_in_user.email != old_email:
            raise ValueError("Old email does not match.")
        if not logged_in_user.check_password(password):
            raise ValueError("Incorrect password.")
        logged_in_user.email = new_email
        return f"Email changed to {new_email} successfully."

# Example usage
if __name__ == "__main__":
    system = SimpleLoginSystem()
    system.register_user("testuser", "oldemail@example.com", "securepassword")
    
    try:
        user = system.login_user("testuser", "securepassword")
        print(system.change_email(user, "oldemail@example.com", "newemail@example.com", "securepassword"))
    except ValueError as e:
        print(e)