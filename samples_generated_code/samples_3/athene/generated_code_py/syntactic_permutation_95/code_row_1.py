import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes) -> str:
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex()

def generate_salt() -> bytes:
    return os.urandom(16)

def register_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, salt BLOB, hashed_password TEXT)''')
    
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)", 
              (username, salt, hashed_password))
    
    conn.commit()
    conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT salt, hashed_password FROM users WHERE username = ?", (username,))
    user = c.fetchone()
    
    if not user:
        return False
    
    salt, stored_hashed_password = user
    hashed_password = hash_password(password, salt)
    
    conn.close()
    return hashed_password == stored_hashed_password

# Example usage:
register_user('john_doe', 'securepassword123')
print(verify_password('john_doe', 'securepassword123'))