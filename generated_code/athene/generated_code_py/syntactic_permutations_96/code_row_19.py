import hashlib
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + key

def register_user(username, password):
    hashed_password = hash_password(password)
    # Assuming a simple dictionary as the database for demonstration
    db = {}
    db[username] = hashed_password
    print(db)

register_user('user1', 'password123')