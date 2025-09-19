import hashlib
import os

class SimpleRegistration:
    def __init__(self):
        self.users = {}

    def generate_salt(self, length=16):
        return os.urandom(length)

    def hash_password(self, password, salt):
        return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

    def register_user(self, username, password):
        if username in self.users:
            raise ValueError("Username already exists")
        
        salt = self.generate_salt()
        hashed_password = self.hash_password(password, salt)
        self.users[username] = {
            'salt': salt.hex(),
            'hashed_password': hashed_password
        }
        print(f"User {username} registered successfully!")

    def verify_user(self, username, password):
        if username not in self.users:
            return False
        
        user_data = self.users[username]
        salt = bytes.fromhex(user_data['salt'])
        hashed_password = self.hash_password(password, salt)
        
        return hashed_password == user_data['hashed_password']

# Example usage
registration_system = SimpleRegistration()
registration_system.register_user("john_doe", "securepassword123")
print(registration_system.verify_user("john_doe", "securepassword123"))  # True
print(registration_system.verify_user("john_doe", "wrongpassword"))      # False