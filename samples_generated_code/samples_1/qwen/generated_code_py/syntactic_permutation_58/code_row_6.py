import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = self._hash_password(password)

    def _hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def check_password(self, password):
        return self._hash_password(password) == self.password_hash

    def update_email(self, new_email):
        self.email = new_email

class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register_user(self, username, email, password):
        if username in self.users:
            raise Exception("Username already exists")
        self.users[username] = User(username, email, password)

    def login_user(self, username, password):
        user = self.users.get(username)
        if user and user.check_password(password):
            self.logged_in_user = user
            return True
        return False

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            raise Exception("User is not logged in")
        
        if self.logged_in_user.email != old_email:
            raise Exception("Old email does not match")
        
        if not self.logged_in_user.check_password(password):
            raise Exception("Password is incorrect")
        
        self.logged_in_user.update_email(new_email)
        return True

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    system.register_user("testuser", "oldemail@example.com", "securepassword123")
    
    if system.login_user("testuser", "securepassword123"):
        try:
            system.change_email("oldemail@example.com", "newemail@example.com", "securepassword123")
            print(f"Email changed to: {system.logged_in_user.email}")
        except Exception as e:
            print(e)
    else:
        print("Login failed")