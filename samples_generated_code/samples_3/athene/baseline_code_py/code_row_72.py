import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_value = salt + hashed_password
    # Assuming a function `save_to_database` exists to save the username and the stored value
    save_to_database(username, stored_value)

def save_to_database(username, stored_value):
    # Placeholder for database saving logic
    print(f"User {username} registered with stored value: {stored_value.hex()}")

# Example usage
register_user('john_doe', 'securepassword123')