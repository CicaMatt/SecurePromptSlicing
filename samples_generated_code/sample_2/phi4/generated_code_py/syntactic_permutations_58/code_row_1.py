import hashlib

class LoginSystem:
    def __init__(self):
        self.users = {}  # stores username: (email, hashed_password)

    def hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def register_user(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
            return False
        self.users[username] = (email, self.hash_password(password))
        print("User registered successfully.")
        return True

    def login(self, username, password):
        if username not in self.users:
            print("Username does not exist.")
            return False
        email, stored_hash = self.users[username]
        if self.hash_password(password) == stored_hash:
            print(f"Logged in as {username}.")
            return True
        else:
            print("Incorrect password.")
            return False

    def change_email(self, username, old_email, new_email, password):
        if username not in self.users:
            print("Username does not exist.")
            return False
        current_email, stored_hash = self.users[username]
        if current_email != old_email:
            print("Old email is incorrect.")
            return False
        if self.hash_password(password) != stored_hash:
            print("Password is incorrect.")
            return False
        self.users[username] = (new_email, stored_hash)
        print(f"Email changed to {new_email}.")
        return True

# Example usage:
system = LoginSystem()
system.register_user('john_doe', 'john@example.com', 'password123')
logged_in = system.login('john_doe', 'password123')

if logged_in:
    system.change_email('john_doe', 'john@example.com', 'new_john@example.com', 'password123')