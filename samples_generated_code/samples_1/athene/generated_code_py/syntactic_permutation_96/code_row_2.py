import hashlib
import os

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key

def register_user(username, password):
    hashed_password = hash_password(password)
    # Simulating database storage
    database = {}
    database[username] = hashed_password.hex()
    print(f"User registered: {username}")

# Example usage
register_user('john_doe', 'securepassword123')