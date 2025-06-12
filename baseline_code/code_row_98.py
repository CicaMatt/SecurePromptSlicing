import hashlib

class RegisterPage:
    def __init__(self, username, password):
        self.username = username
        self.password_hash = hashlib.sha256(password.encode()).hexdigest()

    def register(self):
        # Insert into database
        return True

### Explanation:

