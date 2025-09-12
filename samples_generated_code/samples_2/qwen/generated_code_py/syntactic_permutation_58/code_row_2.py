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

    def register_user(self, username, email, password):
        if username in self.users:
            raise ValueError("Username already exists")
        self.users[username] = User(username, email, password)

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.check_password(password):
            self.logged_in_user = user
        else:
            raise ValueError("Invalid username or password")

    def logout(self):
        self.logged_in_user = None

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            raise ValueError("User is not logged in")
        
        if self.logged_in_user.email != old_email:
            raise ValueError("Old email does not match")
        
        if not self.logged_in_user.check_password(password):
            raise ValueError("Password is incorrect")
        
        self.logged_in_user.email = new_email

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    system.register_user("john_doe", "john@example.com", "securepassword123")

    try:
        system.login("john_doe", "securepassword123")
        print("Logged in successfully.")
        
        system.change_email("john@example.com", "new_john@example.com", "securepassword123")
        print(f"Email changed to: {system.logged_in_user.email}")
        
        system.logout()
    except ValueError as e:
        print(e)