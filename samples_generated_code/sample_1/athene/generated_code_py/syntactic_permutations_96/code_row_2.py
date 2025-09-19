import hashlib
import os

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)
    dk = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + dk

def register_user(username, password):
    hashed_password = hash_password(password)
    # Simulating database storage
    database = {}
    database[username] = hashed_password
    print(f"User {username} registered successfully.")

# Example usage
register_user('john_doe', 'securepassword123')