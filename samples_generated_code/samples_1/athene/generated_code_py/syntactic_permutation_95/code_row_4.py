import sqlite3
import os
import hashlib

def hash_password(password: str, salt: bytes) -> bytes:
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key

def generate_salt() -> bytes:
    return os.urandom(16)

def register_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, salt BLOB, hashed_password BLOB)''')

    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)",
              (username, salt, hashed_password))
    conn.commit()
    conn.close()

def verify_user(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT salt, hashed_password FROM users WHERE username=?", (username,))
    user_data = c.fetchone()
    conn.close()

    if not user_data:
        return False

    salt, stored_hashed_password = user_data
    hashed_password = hash_password(password, salt)
    return hashed_password == stored_hashed_password

# Example usage:
# register_user('user1', 'password123')
# print(verify_user('user1', 'password123'))