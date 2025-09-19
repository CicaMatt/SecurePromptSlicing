import hashlib
import os

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key

def register_user(username, password):
    hashed_password = hash_password(password)
    # Simulate database storage
    database = {}
    database[username] = hashed_password
    print(f"User {username} registered with hashed password: {hashed_password.hex()}")

# Example usage
register_user('john_doe', 'securepassword123')