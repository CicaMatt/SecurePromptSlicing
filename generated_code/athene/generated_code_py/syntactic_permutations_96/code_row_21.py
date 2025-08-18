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
    storage_value = salt + hashed_password
    # Assuming `db` is a pre-existing database connection object with method `execute`
    db.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, storage_value.hex()))

# Example usage:
register_user('john_doe', 'supersecurepassword123')