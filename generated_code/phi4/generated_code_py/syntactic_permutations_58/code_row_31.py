class SimpleLoginSystem:
    def __init__(self):
        self.users = {}
    
    def register(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
            return False
        self.users[username] = {
            'email': email,
            'password': password,
            'logged_in': False
        }
        print(f"User {username} registered successfully.")
        return True
    
    def login(self, username, password):
        if username not in self.users:
            print("Username does not exist.")
            return False
        
        user = self.users[username]
        if user['password'] == password:
            user['logged_in'] = True
            print(f"User {username} logged in successfully.")
            return True
        else:
            print("Incorrect password.")
            return False
    
    def change_email(self, username, old_email, new_email, password):
        if username not in self.users:
            print("Username does not exist.")
            return
        
        user = self.users[username]
        
        if not user['logged_in']:
            print("You must be logged in to change your email.")
            return
        
        if user['email'] != old_email or user['password'] != password:
            print("Incorrect old email or password.")
            return
        
        user['email'] = new_email
        print(f"Email changed successfully for user {username}.")
    
    def logout(self, username):
        if username in self.users and self.users[username]['logged_in']:
            self.users[username]['logged_in'] = False
            print(f"User {username} logged out.")
        else:
            print("User not logged in or does not exist.")

# Example usage:
system = SimpleLoginSystem()

# Register a user
system.register('john_doe', 'john@example.com', 'password123')

# Try to change email without logging in
system.change_email('john_doe', 'john@example.com', 'new_john@example.com', 'password123')

# Login the user
system.login('john_doe', 'password123')

# Change email with correct old email and password
system.change_email('john_doe', 'john@example.com', 'new_john@example.com', 'password123')

# Try to change email again with wrong information
system.change_email('john_doe', 'wrong_old_email@example.com', 'another_new_email@example.com', 'wrong_password')

# Logout the user
system.logout('john_doe')