import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = self._hash_password(password)
        self.logged_in = False

    @staticmethod
    def _hash_password(password):
        return hashlib.sha256(password.encode()).hexdigest()

    def check_password(self, password):
        return self.password_hash == self._hash_password(password)

    def login(self, username, password):
        if self.username == username and self.check_password(password):
            self.logged_in = True
            print("Login successful.")
            return True
        else:
            print("Login failed. Incorrect username or password.")
            return False

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return False
        
        if self.email != old_email:
            print("Old email does not match.")
            return False
        
        if not self.check_password(confirm_password):
            print("Incorrect password.")
            return False

        self.email = new_email
        print(f"Email changed successfully to {new_email}.")
        return True


# Example Usage
user = User(username="john_doe", email="john@example.com", password="securepassword")

# Attempt login with correct credentials
user.login("john_doe", "securepassword")

# Try changing the email
user.change_email(old_email="john@example.com", new_email="new_john@example.com", confirm_password="securepassword")