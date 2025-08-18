import hashlib
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key

def store_user(username, password):
    hashed_password = hash_password(password)
    # Assume 'db' is a pre-defined database connection
    db.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
    db.commit()