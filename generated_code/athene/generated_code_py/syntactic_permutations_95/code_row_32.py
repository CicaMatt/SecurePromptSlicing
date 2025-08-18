import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return key.hex(), salt

def register_user(username: str, password: str):
    hashed_password, salt = hash_password(password)
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, salt BLOB, password_hash TEXT)''')
    c.execute('INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)', (username, salt, hashed_password))
    conn.commit()
    conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('SELECT salt, password_hash FROM users WHERE username=?', (username,))
    user_data = c.fetchone()
    if not user_data:
        return False
    salt, stored_password_hash = user_data
    hashed_password, _ = hash_password(password, salt)
    conn.close()
    return hashed_password == stored_password_hash

# Example usage
register_user('testuser', 'password123')
print(verify_password('testuser', 'password123'))