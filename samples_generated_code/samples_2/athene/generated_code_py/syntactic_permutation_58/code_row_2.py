import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = hashlib.sha256(password.encode()).hexdigest()
        self.logged_in = False

    def login(self, email, password):
        if self.email == email and self.password_hash == hashlib.sha256(password.encode()).hexdigest():
            self.logged_in = True
            return True
        return False

    def change_email(self, old_email, password, new_email):
        if not self.logged_in:
            return "You must be logged in to change your email."
        
        if self.email == old_email and self.password_hash == hashlib.sha256(password.encode()).hexdigest():
            self.email = new_email
            return "Email changed successfully."
        else:
            return "Incorrect old email or password."

# Example usage:
user = User("alice", "alice@example.com", "securepassword")
user.login("alice@example.com", "securepassword")
print(user.change_email("alice@example.com", "securepassword", "newemail@example.com"))