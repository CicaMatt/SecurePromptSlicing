import hashlib
import os

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return (salt.hex(), hashed_password.hex())

def register_user(username, password, db):
    if username in db:
        raise ValueError("Username already exists")
    salt, hashed_password = hash_password(password)
    db[username] = {'salt': salt, 'hashed_password': hashed_password}

db = {}
register_user('user1', 'password123', db)