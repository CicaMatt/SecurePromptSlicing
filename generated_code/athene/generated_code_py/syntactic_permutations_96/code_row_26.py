import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    # Assuming the database connection and user table already exist
    db.execute("INSERT INTO users (username, salt, password) VALUES (?, ?, ?)", (username, salt.hex(), hashed_password.hex()))
    db.commit()