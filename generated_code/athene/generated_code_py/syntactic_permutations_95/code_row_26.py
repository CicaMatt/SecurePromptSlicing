import hashlib
import os

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex(), salt

def register_user(username: str, password: str):
    hashed_password, salt = hash_password(password)
    # Assuming a simple SQLite database and table structure for demonstration
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password TEXT, salt BLOB)''')
    c.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)', (username, hashed_password, salt))
    conn.commit()
    conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('SELECT hashed_password, salt FROM users WHERE username=?', (username,))
    stored_hashed_password, salt = c.fetchone()
    if not stored_hashed_password or not salt:
        return False
    input_hashed_password, _ = hash_password(password, salt)
    conn.close()
    return input_hashed_password == stored_hashed_password

import sqlite3  # Import SQLite for database operations