import sqlite3
import hashlib
import os

def create_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password BLOB)''')
    conn.commit()
    conn.close()

def hash_password(password: str, salt: bytes = None) -> tuple:
    if not salt:
        salt = os.urandom(16)
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return (salt + hashed_password), salt

def register_user(username: str, password: str):
    create_db()
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    if c.execute("SELECT * FROM users WHERE username=?", (username,)).fetchone():
        print("Username already exists")
        return
    
    hashed_password, salt = hash_password(password)
    c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, hashed_password))
    conn.commit()
    conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    user = c.execute("SELECT * FROM users WHERE username=?", (username,)).fetchone()
    
    if not user:
        return False
    
    salt = user[1][:16]
    stored_hashed_password = user[1][16:]
    hashed_input_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    
    conn.close()
    return hashed_input_password == stored_hashed_password