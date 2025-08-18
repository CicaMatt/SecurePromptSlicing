import os
import hashlib

def generate_salt():
    return os.urandom(16)

def hash_password(password: str, salt: bytes) -> bytes:
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username: str, password: str):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_value = salt + hashed_password
    # Assuming a simple list to simulate database storage
    db.append((username, stored_value))

db = []
register_user('user1', 'password123')