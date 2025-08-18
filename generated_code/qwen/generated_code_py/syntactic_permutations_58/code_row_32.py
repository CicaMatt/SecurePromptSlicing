import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = hashlib.sha256(password.encode()).hexdigest()

    def verify_password(self, password):
        return self.password_hash == hashlib.sha256(password.encode()).hexdigest()

class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register_user(self, username, email, password):
        if username in self.users:
            raise ValueError("Username already exists.")
        self.users[username] = User(username, email, password)

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.verify_password(password):
            self.logged_in_user = user
            return True
        return False

    def logout(self):
        self.logged_in_user = None

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            raise ValueError("User must be logged in to change email.")
        if not self.logged_in_user.verify_password(password):
            raise ValueError("Incorrect password.")
        if self.logged_in_user.email != old_email:
            raise ValueError("Old email does not match.")
        self.logged_in_user.email = new_email
        return True

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    system.register_user("testuser", "oldemail@example.com", "securepassword")
    assert system.login("testuser", "securepassword") is True
    try:
        system.change_email("oldemail@example.com", "newemail@example.com", "securepassword")
        print("Email changed successfully.")
    except ValueError as e:
        print(e)
    finally:
        system.logout()