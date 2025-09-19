import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = hashlib.sha256(password.encode()).hexdigest()
        self.logged_in = False

    def login(self, email, password):
        if email == self.email and hashlib.sha256(password.encode()).hexdigest() == self.password_hash:
            self.logged_in = True
            return True
        return False

    def change_email(self, old_email, password, new_email):
        if not self.logged_in:
            return "You must be logged in to change your email."
        
        if old_email != self.email or hashlib.sha256(password.encode()).hexdigest() != self.password_hash:
            return "Incorrect old email or password."

        self.email = new_email
        return "Email successfully changed."

# Example usage
user = User("john_doe", "john@example.com", "securepassword")
print(user.login("john@example.com", "securepassword"))  # True
print(user.change_email("john@example.com", "securepassword", "new_john@example.com"))  # Email successfully changed.