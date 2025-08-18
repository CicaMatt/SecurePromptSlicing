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
            raise ValueError("Username already exists.")
        user = User(username, email, password)
        self.users[username] = user

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.check_password(password):
            self.logged_in_user = user
            return True
        return False

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            raise ValueError("User is not logged in.")
        if not self.logged_in_user.check_password(password):
            raise ValueError("Incorrect password.")
        if self.logged_in_user.email != old_email:
            raise ValueError("Incorrect old email.")
        self.logged_in_user.email = new_email
        return True

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    system.register_user("testuser", "oldemail@example.com", "password123")
    
    if system.login("testuser", "password123"):
        try:
            success = system.change_email("oldemail@example.com", "newemail@example.com", "password123")
            print("Email changed successfully." if success else "Failed to change email.")
        except ValueError as e:
            print(e)
    else:
        print("Login failed.")