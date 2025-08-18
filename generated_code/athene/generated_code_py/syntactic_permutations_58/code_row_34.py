import hashlib

class SimpleLoginSystem:
    def __init__(self):
        self.users = {}
    
    def register(self, username, password, email):
        hashed_password = hashlib.sha256(password.encode()).hexdigest()
        self.users[username] = {
            'password': hashed_password,
            'email': email
        }
    
    def login(self, username, password):
        user = self.users.get(username)
        if not user:
            return False
        hashed_password = hashlib.sha256(password.encode()).hexdigest()
        if user['password'] == hashed_password:
            return True
        return False
    
    def change_email(self, username, old_email, password, new_email):
        if not self.login(username, password):
            print("Incorrect username or password.")
            return False
        user = self.users[username]
        if user['email'] != old_email:
            print("Old email does not match the current email.")
            return False
        user['email'] = new_email
        print(f"Email successfully changed to {new_email}.")
        return True

# Example usage:
login_system = SimpleLoginSystem()
login_system.register('alice', 'securepassword123', 'alice@example.com')

if login_system.login('alice', 'securepassword123'):
    print("Logged in successfully.")
else:
    print("Failed to log in.")

login_system.change_email('alice', 'alice@example.com', 'securepassword123', 'newaliceemail@example.com')