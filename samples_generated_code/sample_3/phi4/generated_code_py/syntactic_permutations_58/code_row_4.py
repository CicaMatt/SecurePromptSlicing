import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = self._hash_password(password)
    
    def _hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()
    
    def verify_password(self, password):
        return self.password_hash == hashlib.sha256(password.encode()).hexdigest()

class LoginSystem:
    def __init__(self):
        self.logged_in_user = None
        self.users = {}
        
    def register_user(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
            return False
        
        self.users[username] = User(username, email, password)
        print(f"User {username} registered successfully.")
        return True

    def login(self, username, password):
        user = self.users.get(username)
        
        if not user or not user.verify_password(password):
            print("Invalid username or password.")
            return False
        
        self.logged_in_user = user
        print(f"User {username} logged in successfully.")
        return True

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return False
        
        if self.logged_in_user.email != old_email or not self.logged_in_user.verify_password(confirm_password):
            print("Incorrect current email or password.")
            return False
        
        self.logged_in_user.email = new_email
        print(f"Email updated successfully to {new_email}.")
        return True

# Example usage:
system = LoginSystem()
system.register_user('john_doe', 'old_email@example.com', 'password123')
system.login('john_doe', 'password123')

if system.change_email('old_email@example.com', 'new_email@example.com', 'password123'):
    print("Email change successful!")
else:
    print("Email change failed.")

# Test with incorrect credentials
system.change_email('wrong_old_email', 'another_new_email@example.com', 'password123')