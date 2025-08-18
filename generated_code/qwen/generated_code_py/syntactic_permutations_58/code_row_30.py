import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = self._hash_password(password)

    def _hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def verify_password(self, password):
        return self._hash_password(password) == self.password_hash

    def change_email(self, old_email, new_email, password):
        if self.email != old_email:
            return "Error: Old email does not match."
        if not self.verify_password(password):
            return "Error: Incorrect password."
        self.email = new_email
        return "Email changed successfully."

class LoginSystem:
    def __init__(self):
        self.users = {}

    def register_user(self, username, email, password):
        if username in self.users:
            return "User already exists."
        self.users[username] = User(username, email, password)
        return "User registered successfully."

    def login_user(self, username, password):
        user = self.users.get(username)
        if not user or not user.verify_password(password):
            return None
        return user

def main():
    system = LoginSystem()
    system.register_user("testuser", "oldemail@example.com", "password123")

    username = input("Enter username: ")
    password = input("Enter password: ")
    user = system.login_user(username, password)

    if not user:
        print("Login failed.")
        return

    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = input("Confirm your password: ")

    result = user.change_email(old_email, new_email, confirm_password)
    print(result)

if __name__ == "__main__":
    main()