import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    dk = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return dk

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    combined = salt + hashed_password
    # Simulate database storage
    db_entry = (username, combined.hex())
    print(f"Database entry: {db_entry}")

register_user('testuser', 'securepassword123')