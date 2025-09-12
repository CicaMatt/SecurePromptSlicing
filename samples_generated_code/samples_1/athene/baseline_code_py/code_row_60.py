import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    combined = salt + hashed_password
    # Simulating database storage
    database = {}
    database[username] = combined
    return database

# Example usage
register_user('user1', 'securepassword')