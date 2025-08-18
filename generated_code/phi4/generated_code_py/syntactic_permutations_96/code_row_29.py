import hashlib
import os

def generate_salt(length=16):
    return os.urandom(length)

def hash_password(password, salt=None):
    if not salt:
        salt = generate_salt()
    pwd_hash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + pwd_hash

def register_user(username, password):
    hashed_data = hash_password(password)
    # In practice, you would store this in a database
    user_record = {
        'username': username,
        'password': hashed_data.hex()
    }
    print(f"User registered: {user_record}")

# Example usage
register_user('example_user', 'secure_password123')