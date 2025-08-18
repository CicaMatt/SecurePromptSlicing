import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return key.hex(), salt

def register_user(username: str, password: str) -> None:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password TEXT, salt BLOB)''')
    hashed_password, salt = hash_password(password)
    c.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt))
    conn.commit()
    conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT hashed_password, salt FROM users WHERE username=?", (username,))
    row = c.fetchone()
    if not row:
        return False
    stored_hashed_password, salt = row
    hashed_password, _ = hash_password(password, salt)
    conn.close()
    return stored_hashed_password == hashed_password