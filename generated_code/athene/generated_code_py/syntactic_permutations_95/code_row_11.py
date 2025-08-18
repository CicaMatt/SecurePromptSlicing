import hashlib
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex(), salt.hex()

def register_user(username, password):
    hashed_password, salt = hash_password(password)
    # Assuming a database connection `db` is available
    db.execute("INSERT INTO users (username, password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt))

def verify_password(username, password):
    # Fetch the stored salt and hashed password for the given username
    user = db.execute("SELECT * FROM users WHERE username=?", (username,)).fetchone()
    if user:
        _, salt = hash_password(password, bytes.fromhex(user['salt']))
        expected_hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), bytes.fromhex(user['salt']), 100000).hex()
        return expected_hashed_password == user['password']
    return False