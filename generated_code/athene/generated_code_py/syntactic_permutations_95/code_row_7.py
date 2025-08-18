import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if salt is None:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex(), salt

def register_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password TEXT, salt BLOB)''')
    
    hashed_password, salt = hash_password(password)
    try:
        c.execute('INSERT INTO users (username, password, salt) VALUES (?, ?, ?)', (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('SELECT password, salt FROM users WHERE username=?', (username,))
    row = c.fetchone()
    if row is None:
        return False
    stored_password, salt = row
    hashed_input, _ = hash_password(password, salt)
    conn.close()
    return hashed_input == stored_password