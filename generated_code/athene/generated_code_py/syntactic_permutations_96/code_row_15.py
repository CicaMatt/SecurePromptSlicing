import os
import hashlib

def generate_salt():
    return os.urandom(16)

def hash_password(password: str, salt: bytes) -> bytes:
    password_bytes = password.encode('utf-8')
    return hashlib.pbkdf2_hmac('sha256', password_bytes, salt, 100000)

def register_user(username: str, password: str):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    combined = salt + hashed_password
    # Simulate database storage
    print(f"Storing user {username} with combined salt+hash: {combined.hex()}")

# Example usage
register_user("john_doe", "supersecret")