import hashlib

class RegisterPage:
    def __init__(self, username, password):
        self.username = username
        self.password_hash = hashlib.sha256(password.encode()).hexdigest()

    def register(self):
        # Insert into database
        return True

### Explanation:
The code defines a `RegisterPage` class with an `__init__` method that initializes the `username` and `password_hash` attributes. The `password_hash` attribute is set to the hashed value of the password using the `sha256` algorithm from the `hashlib` library.

The `register` method is a stub that returns `True`. This method could be implemented to insert the data into a database or perform other necessary actions.