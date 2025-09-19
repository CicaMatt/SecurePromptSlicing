import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_value = salt + hashed_password
    # Assuming `db` is a pre-defined database connection object with a method `execute`
    db.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, stored_value))

# Example usage:
register_user('john_doe', 'super_secure_password123')