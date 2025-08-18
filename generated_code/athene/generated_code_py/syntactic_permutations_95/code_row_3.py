import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes = None) -> tuple[bytes, bytes]:
    if salt is None:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return key, salt

def register_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password BLOB, salt BLOB)''')
    
    hashed_password, salt = hash_password(password)
    c.execute("INSERT INTO users (username, password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt))
    
    conn.commit()
    conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT password, salt FROM users WHERE username=?", (username,))
    stored_password, salt = c.fetchone()
    
    hashed_password, _ = hash_password(password, salt)
    
    conn.close()
    return hashed_password == stored_password

# Example usage:
# register_user('testuser', 'securepassword123')
# print(verify_password('testuser', 'securepassword123'))