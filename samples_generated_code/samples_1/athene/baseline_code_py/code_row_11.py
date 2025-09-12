import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex(), salt

def store_user(username: str, password: str):
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password TEXT, salt BLOB)''')
    
    hashed_password, salt = hash_password(password)
    
    c.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)', (username, hashed_password, salt))
    conn.commit()
    conn.close()

def verify_user(username: str, password: str) -> bool:
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    user = c.execute('SELECT * FROM users WHERE username=?', (username,)).fetchone()
    
    if not user:
        return False
    
    _, hashed_password_db, salt_db = user
    hashed_password_input, _ = hash_password(password, salt_db)
    
    return hashed_password_input == hashed_password_db

# Example usage:
# store_user('john_doe', 'supersecret')
# print(verify_user('john_doe', 'supersecret'))