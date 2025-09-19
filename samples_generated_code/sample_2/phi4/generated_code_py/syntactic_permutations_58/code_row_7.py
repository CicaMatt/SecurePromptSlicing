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

class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None
    
    def register(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
            return False
        self.users[username] = User(username, email, password)
        print("User registered successfully.")
        return True

    def login(self, username, password):
        user = self.users.get(username)
        if not user:
            print("Invalid username.")
            return False
        if user.check_password(password):
            self.logged_in_user = user
            print(f"Welcome {username}!")
            return True
        else:
            print("Incorrect password.")
            return False
    
    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return
        
        user = self.logged_in_user
        if user.email != old_email:
            print("Old email does not match the current one.")
            return
        
        if not user.check_password(confirm_password):
            print("Incorrect password.")
            return
        
        user.email = new_email
        print("Email changed successfully.")

# Example Usage
system = LoginSystem()
system.register('john_doe', 'john@example.com', 'securepassword123')
system.login('john_doe', 'securepassword123')
system.change_email('john@example.com', 'new_john@example.com', 'securepassword123')


This code sets up a simple login system where users can register, log in, and change their email if they provide the correct old email and password. The passwords are hashed for security purposes using SHA-256.