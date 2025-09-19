import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    hasher = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return hasher

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_value = salt + hashed_password
    # Simulate storing in a database
    print(f"Storing username: {username}, salt+hash: {stored_value.hex()}")

# Example usage
register_user('user1', 'password123')