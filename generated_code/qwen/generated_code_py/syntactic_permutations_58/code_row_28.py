import hashlib

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password_hash = self._hash_password(password)
        self.email = email

    def _hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def check_password(self, password):
        return self.password_hash == self._hash_password(password)

class LoginSystem:
    def __init__(self):
        self.users = {}

    def register_user(self, username, password, email):
        if username in self.users:
            raise ValueError("Username already exists.")
        self.users[username] = User(username, password, email)
        print(f"User {username} registered successfully.")

    def login_user(self, username, password):
        user = self.users.get(username)
        if not user or not user.check_password(password):
            raise ValueError("Invalid username or password.")
        print(f"User {username} logged in successfully.")
        return user

    def change_email(self, user, old_email, new_email, password):
        if not user.check_password(password):
            raise ValueError("Incorrect password.")
        if user.email != old_email:
            raise ValueError("Incorrect old email.")
        user.email = new_email
        print(f"Email changed to {new_email} successfully.")

# Example usage
if __name__ == "__main__":
    login_system = LoginSystem()
    try:
        # Register a new user
        login_system.register_user("testuser", "securepassword123", "oldemail@example.com")
        
        # Log in the user
        logged_in_user = login_system.login_user("testuser", "securepassword123")
        
        # Change email
        login_system.change_email(logged_in_user, "oldemail@example.com", "newemail@example.com", "securepassword123")
    except ValueError as e:
        print(e)