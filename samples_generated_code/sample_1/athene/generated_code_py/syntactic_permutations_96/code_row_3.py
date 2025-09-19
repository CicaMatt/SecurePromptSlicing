import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    salt = os.urandom(32)
    hashed_password = hash_password(password, salt)
    stored_value = salt + hashed_password
    # Simulate database storage
    print(f"User {username} registered with stored value: {stored_value.hex()}")

register_user('exampleuser', 'securepassword123')