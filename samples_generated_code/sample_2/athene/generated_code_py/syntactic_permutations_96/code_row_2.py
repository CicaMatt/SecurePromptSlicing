import hashlib
import os

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)
    else:
        salt = bytes.fromhex(salt)
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt.hex() + key.hex()

def register_user(username, password):
    hashed_password = hash_password(password)
    # Simulate storing in a database
    print(f"User {username} registered with hashed password: {hashed_password}")

# Example usage
register_user('john_doe', 'securepassword123')