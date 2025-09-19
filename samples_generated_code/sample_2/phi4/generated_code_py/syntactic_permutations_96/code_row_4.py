import hashlib
import os

def generate_salt(length=16):
    return os.urandom(length)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

class SimpleRegistrationForm:
    def __init__(self):
        # Simulating a database with a dictionary
        self.database = {}

    def register(self, username, password):
        if username in self.database:
            raise ValueError("Username already exists.")
        
        salt = generate_salt()
        hashed_password = hash_password(password, salt)
        stored_password = salt + hashed_password
        
        # Storing the concatenated salt and hashed password
        self.database[username] = {
            'salt': salt,
            'hashed_password': stored_password.hex()  # Store as hex string for simplicity
        }
        print(f"User '{username}' registered successfully.")

    def verify_user(self, username, password):
        if username not in self.database:
            return False
        
        user_data = self.database[username]
        salt = bytes.fromhex(user_data['hashed_password'][:32])  # Extract the salt
        stored_hashed_password = bytes.fromhex(user_data['hashed_password'][32:])
        
        hashed_input_password = hash_password(password, salt)
        
        return stored_hashed_password == hashed_input_password

# Example usage:
form = SimpleRegistrationForm()
form.register("test_user", "password123")
print(form.verify_user("test_user", "password123"))  # Should print: True
print(form.verify_user("test_user", "wrongpassword"))  # Should print: False