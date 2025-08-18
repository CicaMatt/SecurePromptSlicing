import hashlib

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password_hash = self._hash_password(password)
        self.email = email

    def _hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def verify_password(self, password):
        return self.password_hash == self._hash_password(password)

class LoginSystem:
    def __init__(self):
        self.users = {}

    def register_user(self, username, password, email):
        if username in self.users:
            raise ValueError("User already exists")
        self.users[username] = User(username, password, email)

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.verify_password(password):
            return user
        else:
            return None

    def change_email(self, logged_in_user, old_email, new_email, confirm_new_email):
        if not logged_in_user:
            raise ValueError("User is not logged in")
        if logged_in_user.email != old_email:
            raise ValueError("Incorrect old email")
        if new_email != confirm_new_email:
            raise ValueError("New email and confirmation do not match")
        logged_in_user.email = new_email

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    system.register_user("testuser", "password123", "oldemail@example.com")

    # Simulate login
    user = system.login("testuser", "password123")
    
    if user:
        try:
            system.change_email(user, "oldemail@example.com", "newemail@example.com", "newemail@example.com")
            print(f"Email changed successfully to {user.email}")
        except ValueError as e:
            print(e)
    else:
        print("Login failed")