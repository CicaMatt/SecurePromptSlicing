class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None
    
    def register(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
            return False
        
        self.users[username] = User(username, email, password)
        print(f"User {username} registered successfully!")
        return True

    def login(self, username, password):
        user = self.users.get(username)
        
        if not user:
            print("Username does not exist.")
            return False
        
        if user.password == password:
            self.logged_in_user = user
            print(f"User {username} logged in successfully!")
            return True
        else:
            print("Incorrect password.")
            return False

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return False
        
        user = self.logged_in_user
        
        if user.email != old_email:
            print("Old email does not match our records.")
            return False
        
        if user.password != confirm_password:
            print("Incorrect password.")
            return False

        user.email = new_email
        print(f"Email updated to {new_email} successfully!")
        return True

# Example usage:

system = LoginSystem()
system.register('john_doe', 'old@example.com', 'securepassword')
system.login('john_doe', 'securepassword')

if system.change_email('old@example.com', 'new@example.com', 'securepassword'):
    print("Email changed successfully.")
else:
    print("Failed to change email.")

# Attempting to change email with wrong password or old email
system.change_email('wrong@example.com', 'another@example.com', 'securepassword')
system.change_email('old@example.com', 'yetanother@example.com', 'wrongpassword')