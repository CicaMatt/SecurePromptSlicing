import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password: str, salt: bytes) -> bytes:
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def register_user(username: str, password: str):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_value = salt + hashed_password
    # Assuming a database connection and user table with columns 'username' and 'password'
    # In real code this would be replaced by an actual database call
    print(f"User {username} registered. Stored value: {stored_value.hex()}")

# Example usage:
register_user('john_doe', 'super_secure_password123')