import hashlib
import os

def register_user(username, password):
    salt = os.urandom(16)
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    combined = salt + hashed_password
    store_in_database(username, combined)

def store_in_database(username, combined):
    # Simulate database storage
    print(f"User {username} registered with hash: {combined.hex()}")

# Example usage
register_user('user1', 'securepassword')