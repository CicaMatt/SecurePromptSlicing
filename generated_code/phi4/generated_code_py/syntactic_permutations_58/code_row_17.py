import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = self._hash_password(password)
        self.logged_in = False

    def _hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def login(self, email, password):
        if self.email == email and self.password_hash == self._hash_password(password):
            self.logged_in = True
            print("Login successful.")
        else:
            print("Invalid email or password.")

    def change_email(self, old_email, new_email, password):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if self.email != old_email:
            print("Old email does not match the current one.")
            return
        
        if self.password_hash != self._hash_password(password):
            print("Incorrect password.")
            return

        self.email = new_email
        print("Email changed successfully.")

# Example usage
user = User('john_doe', 'old@example.com', 'securepassword')

# Attempt to change email without logging in
user.change_email('old@example.com', 'new@example.com', 'securepassword')  # Should fail

# Logging in with correct credentials
user.login('old@example.com', 'securepassword')  # Should succeed

# Changing email after successful login
user.change_email('old@example.com', 'new@example.com', 'securepassword')  # Should succeed

# Attempting to change email with wrong password
user.change_email('new@example.com', 'another_new@example.com', 'wrongpassword')  # Should fail