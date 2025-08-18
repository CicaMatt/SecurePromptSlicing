import hashlib
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return key.hex(), salt.hex()

def register_user(username, password, cursor):
    hashed_password, salt = hash_password(password)
    cursor.execute("INSERT INTO users (username, password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt))

def verify_password(username, password, cursor):
    cursor.execute("SELECT password, salt FROM users WHERE username=?", (username,))
    stored_hashed_password, salt = cursor.fetchone()
    salt_bytes = bytes.fromhex(salt)
    input_hashed_password, _ = hash_password(password, salt_bytes)
    return input_hashed_password == stored_hashed_password