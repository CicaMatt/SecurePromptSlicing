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
        self.logged_in_user = None

    def register_user(self, username, password, email):
        if username in self.users:
            raise ValueError("Username already exists.")
        self.users[username] = User(username, password, email)

    def login(self, username, password):
        user = self.users.get(username)
        if not user or not user.verify_password(password):
            return False
        self.logged_in_user = user
        return True

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            raise ValueError("User is not logged in.")
        if self.logged_in_user.email != old_email or not self.logged_in_user.verify_password(password):
            raise ValueError("Incorrect old email or password.")
        self.logged_in_user.email = new_email
        return True

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    system.register_user("testuser", "password123", "oldemail@example.com")
    
    if system.login("testuser", "password123"):
        try:
            system.change_email("oldemail@example.com", "newemail@example.com", "password123")
            print(f"Email changed to {system.logged_in_user.email}")
        except ValueError as e:
            print(e)
    else:
        print("Login failed.")