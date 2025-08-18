import sqlite3
import os
import hashlib

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return key.hex(), salt

def register_user(username: str, password: str) -> None:
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT, salt BLOB)''')
    
    hashed_password, salt = hash_password(password)
    cursor.execute("INSERT INTO users (username, password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt))
    conn.commit()
    conn.close()

# Example usage
register_user('john_doe', 'supersecret')