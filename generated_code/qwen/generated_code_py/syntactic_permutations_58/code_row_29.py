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
    
    def login(self, username, password):
        user = self.users.get(username)
        if user and user.check_password(password):
            return user
        else:
            return None

    def change_email(self, logged_in_user, old_email, new_email, password):
        if logged_in_user.email != old_email or not logged_in_user.check_password(password):
            raise ValueError("Incorrect old email or password.")
        logged_in_user.email = new_email

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    system.register_user("john_doe", "securepassword123", "john@example.com")
    
    user = system.login("john_doe", "securepassword123")
    if user:
        try:
            system.change_email(user, "john@example.com", "new_john@example.com", "securepassword123")
            print(f"Email changed to {user.email}")
        except ValueError as e:
            print(e)
    else:
        print("Login failed.")