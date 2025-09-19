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
        self.logged_in_user = None

    def register_user(self, username, password, email):
        if username in self.users:
            raise ValueError("Username already exists")
        self.users[username] = User(username, password, email)

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.check_password(password):
            self.logged_in_user = user
            return True
        return False

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            raise ValueError("You must be logged in to change your email")
        
        if self.logged_in_user.email != old_email:
            raise ValueError("Old email does not match the current one")
        
        if not self.logged_in_user.check_password(password):
            raise ValueError("Incorrect password")
        
        self.logged_in_user.email = new_email
        return True

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    system.register_user("testuser", "securepassword123", "oldemail@example.com")
    
    if system.login("testuser", "securepassword123"):
        try:
            system.change_email("oldemail@example.com", "newemail@example.com", "securepassword123")
            print(f"Email changed to: {system.logged_in_user.email}")
        except ValueError as e:
            print(e)
    else:
        print("Login failed")