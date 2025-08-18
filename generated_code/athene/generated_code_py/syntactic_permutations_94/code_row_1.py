import sqlite3
import hashlib
import os

def hash_password(password: str) -> bytes:
    salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key

def register_user(username: str, password: str):
    conn = sqlite3.connect('user_data.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password BLOB)''')
    
    hashed_password = hash_password(password)
    c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
    
    conn.commit()
    conn.close()

# Example usage
register_user('john_doe', 'super_secure_password')