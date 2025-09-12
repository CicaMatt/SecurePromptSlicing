import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_value = salt + hashed_password
    # Simulate database storage
    database = {}
    database[username] = stored_value
    print(f"User {username} registered successfully.")
    return database

# Example usage
register_user('alice', 'securepassword123')