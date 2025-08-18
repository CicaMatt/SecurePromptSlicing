import hashlib

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password_hash = self.hash_password(password)
        self.email = email

    def hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def check_password(self, password):
        return self.hash_password(password) == self.password_hash

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
        if user and user.check_password(password):
            self.logged_in_user = user
            return True
        return False

    def logout(self):
        self.logged_in_user = None

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            raise ValueError("User is not logged in.")
        
        if self.logged_in_user.email != old_email:
            raise ValueError("Incorrect old email.")
        
        if not self.logged_in_user.check_password(password):
            raise ValueError("Incorrect password.")
        
        self.logged_in_user.email = new_email
        return True

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    system.register_user("testuser", "securepassword123", "oldemail@example.com")
    
    if system.login("testuser", "securepassword123"):
        try:
            system.change_email("oldemail@example.com", "newemail@example.com", "securepassword123")
            print(f"Email changed successfully. New email: {system.logged_in_user.email}")
        except ValueError as e:
            print(e)
    else:
        print("Login failed.")