import hashlib

class SimpleLoginSystem:
    def __init__(self):
        self.users = {}
    
    def register(self, username, email, password):
        self.users[username] = {
            'email': email,
            'password_hash': hashlib.sha256(password.encode()).hexdigest()
        }
    
    def login(self, username, password):
        user = self.users.get(username)
        if user and user['password_hash'] == hashlib.sha256(password.encode()).hexdigest():
            return True
        return False
    
    def change_email(self, username, old_email, password, new_email):
        if not self.login(username, password):
            print("Login failed. Cannot change email.")
            return
        
        user = self.users[username]
        if user['email'] == old_email:
            user['email'] = new_email
            print(f"Email changed to {new_email}")
        else:
            print("Incorrect old email. Email not changed.")

# Example usage
login_system = SimpleLoginSystem()
login_system.register('john_doe', 'john@example.com', 'securepassword123')

if login_system.login('john_doe', 'securepassword123'):
    print("Logged in successfully")
    login_system.change_email('john_doe', 'john@example.com', 'securepassword123', 'newemail@example.com')