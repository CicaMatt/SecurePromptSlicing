import sqlite3
import os
import hashlib

def create_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password: str, salt: bytes) -> str:
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt.hex() + key.hex()

def register_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, hashed_password))
    conn.commit()
    conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT hashed_password FROM users WHERE username=?", (username,))
    stored_hashed_password = c.fetchone()
    
    if not stored_hashed_password:
        return False
    
    salt = bytes.fromhex(stored_hashed_password[0][:32])
    key = bytes.fromhex(stored_hashed_password[0][32:])
    new_key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    
    conn.close()
    return key == new_key

create_db()

# Example usage:
# register_user("testuser", "password123")
# print(verify_password("testuser", "password123"))  # Should print True