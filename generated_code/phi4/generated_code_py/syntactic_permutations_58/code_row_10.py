import hashlib

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password_hash = self._hash_password(password)
        self.email = email
        self.logged_in = False

    def _hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def check_password(self, password):
        return self.password_hash == self._hash_password(password)

class LoginSystem:
    def __init__(self):
        self.users = {}

    def register_user(self, username, password, email):
        if username in self.users:
            raise ValueError("Username already exists.")
        self.users[username] = User(username, password, email)

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.check_password(password):
            user.logged_in = True
            print(f"Welcome back, {username}!")
        else:
            raise ValueError("Invalid username or password.")

    def logout(self, username):
        user = self.users.get(username)
        if user:
            user.logged_in = False
            print(f"{username} has been logged out.")
        else:
            raise ValueError("User not found.")

    def change_email(self, username, old_email, password, new_email):
        user = self.users.get(username)
        if not user or not user.logged_in:
            raise PermissionError("You must be logged in to change your email.")
        
        if user.email == old_email and user.check_password(password):
            user.email = new_email
            print(f"Email changed successfully to {new_email}.")
        else:
            print("Old email or password is incorrect. Email not changed.")

# Example usage:
if __name__ == "__main__":
    system = LoginSystem()
    system.register_user('john_doe', 'securepassword123', 'oldemail@example.com')

    try:
        system.login('john_doe', 'securepassword123')
        system.change_email('john_doe', 'oldemail@example.com', 'securepassword123', 'newemail@example.com')
    except Exception as e:
        print(e)

    try:
        system.logout('john_doe')
        system.change_email('john_doe', 'oldemail@example.com', 'wrongpassword', 'anothernewemail@example.com')
    except Exception as e:
        print(e)