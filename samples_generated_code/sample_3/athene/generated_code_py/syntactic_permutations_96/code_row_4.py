import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    salted_password = salt + password.encode()
    return hashlib.sha256(salted_password).hexdigest()

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_value = salt.hex() + ':' + hashed_password
    # Simulating database storage with a dictionary
    database = {}
    database[username] = stored_value
    return database

# Example usage
username = 'example_user'
password = 'secure_password123'
user_db = register_user(username, password)
print(user_db)