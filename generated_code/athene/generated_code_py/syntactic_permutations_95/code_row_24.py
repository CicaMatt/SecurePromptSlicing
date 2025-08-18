import hashlib
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + key

def register_user(username, password):
    salted_hash = hash_password(password)
    # Assuming you have a database connection `db` and a table `users`
    db.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, salted_hash))

# Example usage:
register_user('john_doe', 'supersecurepassword123')