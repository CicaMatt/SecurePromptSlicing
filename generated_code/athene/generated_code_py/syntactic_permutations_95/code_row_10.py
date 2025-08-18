import hashlib
import os

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex(), salt

def register_user(name: str, password: str):
    hashed_password, salt = hash_password(password)
    # Assuming a simple SQLite database for demonstration
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (name TEXT, salt BLOB, password TEXT)''')
    c.execute("INSERT INTO users (name, salt, password) VALUES (?, ?, ?)", (name, salt, hashed_password))
    conn.commit()
    conn.close()

def verify_password(name: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT salt, password FROM users WHERE name=?", (name,))
    user_data = c.fetchone()
    if not user_data:
        return False
    salt, stored_password = user_data
    hashed_password, _ = hash_password(password, salt)
    conn.close()
    return hashed_password == stored_password

import sqlite3
# Example usage:
register_user('Alice', 'securepassword123')
print(verify_password('Alice', 'securepassword123'))