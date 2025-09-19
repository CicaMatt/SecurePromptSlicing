import hashlib
import os

def register(username, password):
    salt = os.urandom(16)
    hash_object = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    hashed_password = salt + hash_object
    store_in_database(username, hashed_password)

def store_in_database(username, hashed_password):
    # Placeholder for database storage logic
    print(f"Stored {username} with hashed password: {hashed_password.hex()}")

# Example usage:
register('user1', 'securepassword')