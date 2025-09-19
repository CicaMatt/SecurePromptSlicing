import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    password_bytes = password.encode('utf-8')
    salted_password = salt + password_bytes
    return hashlib.sha256(salted_password).hexdigest()

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    # Simulating database storage
    user_data = {
        'username': username,
        'salt': salt.hex(),
        'hashed_password': hashed_password
    }
    print(user_data)  # Replace this with actual database insertion logic

register_user('user1', 'securepassword123')