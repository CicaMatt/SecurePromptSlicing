import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    key = hashlib.pbkdf2_hmac(
        'sha256',  # The hash digest algorithm for HMAC
        password.encode('utf-8'),  # Convert the password to bytes
        salt,  # Provide the salt
        100000  # It is recommended to use at least 100,000 iterations of SHA-256 
    )
    return key

def store_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_data = salt + hashed_password
    # Simulating database storage with a dictionary
    database[username] = stored_data
    print(f"User {username} registered successfully.")

# Simulated database
database = {}

# Example usage
store_user("exampleuser", "examplepassword")