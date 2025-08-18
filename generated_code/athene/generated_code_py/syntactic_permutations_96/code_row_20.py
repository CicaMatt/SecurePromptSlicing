import hashlib
import os

def register_user(username, password):
    salt = os.urandom(16)
    hash_object = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    hashed_password = salt + hash_object
    # Assuming `db` is a pre-defined database connection object
    db.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, hashed_password))

# Example usage:
register_user('john_doe', 'securepassword123')