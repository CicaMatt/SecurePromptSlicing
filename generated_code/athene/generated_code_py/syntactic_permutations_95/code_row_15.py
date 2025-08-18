import hashlib
import os

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex(), salt

def register(username: str, password: str) -> None:
    hashed_password, salt = hash_password(password)
    # Assuming a simple dictionary to simulate database storage
    db[username] = {'hashed_password': hashed_password, 'salt': salt}

def verify_login(username: str, password: str) -> bool:
    user = db.get(username)
    if not user:
        return False
    stored_salt = user['salt']
    stored_hashed_password = user['hashed_password']
    input_hashed_password, _ = hash_password(password, stored_salt)
    return input_hashed_password == stored_hashed_password

db = {}  # Simulating a database with a dictionary