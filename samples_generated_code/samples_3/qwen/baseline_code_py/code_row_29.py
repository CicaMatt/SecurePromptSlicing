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

    def change_email(self, old_email, new_email, password):
        if self.email != old_email:
            print("Error: Old email does not match.")
            return False
        if not self.check_password(password):
            print("Error: Incorrect password.")
            return False
        self.email = new_email
        print("Email changed successfully.")
        return True

class LoginSystem:
    def __init__(self):
        self.users = {}

    def register_user(self, username, password, email):
        if username in self.users:
            print("Error: Username already exists.")
            return False
        self.users[username] = User(username, password, email)
        print("User registered successfully.")
        return True

    def login_user(self, username, password):
        user = self.users.get(username)
        if user and user.check_password(password):
            print("Login successful.")
            return user
        else:
            print("Error: Invalid username or password.")
            return None

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    system.register_user("testuser", "securepassword123", "oldemail@example.com")
    
    user = system.login_user("testuser", "securepassword123")
    if user:
        user.change_email("oldemail@example.com", "newemail@example.com", "securepassword123")