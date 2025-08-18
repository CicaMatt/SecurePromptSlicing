import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    hash_object = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return hash_object

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_value = salt + hashed_password
    # Simulate database storage
    print(f"User {username} registered with stored value: {stored_value.hex()}")

# Example usage
register_user('john_doe', 'mysecretpassword')