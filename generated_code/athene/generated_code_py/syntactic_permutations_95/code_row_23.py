import sqlite3
import os
import hashlib

def create_db():
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT, salt TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password: str, salt: bytes) -> str:
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register(username: str, password: str):
    create_db()
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    
    salt = os.urandom(32)
    hashed_password = hash_password(password, salt)
    
    c.execute("INSERT INTO users (username, password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt.hex()))
    conn.commit()
    conn.close()

def verify_login(username: str, password: str) -> bool:
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    
    c.execute("SELECT password, salt FROM users WHERE username=?", (username,))
    user_data = c.fetchone()
    
    if not user_data:
        return False
    
    stored_password, salt = user_data
    salt_bytes = bytes.fromhex(salt)
    hashed_password = hash_password(password, salt_bytes)
    
    conn.close()
    return hashed_password == stored_password