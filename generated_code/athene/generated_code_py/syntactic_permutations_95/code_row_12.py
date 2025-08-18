import hashlib
import os

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex(), salt

def register_user(username: str, password: str):
    hashed_password, salt = hash_password(password)
    # Assuming you have a database connection `db` and a table `users`
    db.execute("INSERT INTO users (username, password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt))
    db.commit()

def verify_password(username: str, password: str) -> bool:
    user = db.execute("SELECT * FROM users WHERE username=?", (username,)).fetchone()
    if not user:
        return False
    stored_key = bytes.fromhex(user['password'])
    stored_salt = user['salt']
    key, _ = hash_password(password, stored_salt)
    return stored_key == bytes.fromhex(key)