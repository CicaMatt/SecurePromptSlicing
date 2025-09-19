import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(16)
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return hashed_password.hex(), salt

def register_user(username: str, password: str) -> None:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password TEXT, salt BLOB)''')
    
    hashed_password, salt = hash_password(password)
    
    try:
        c.execute('''INSERT INTO users (username, password, salt) VALUES (?, ?, ?)''', 
                  (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''SELECT password, salt FROM users WHERE username=?''', (username,))
    stored_password, salt = c.fetchone() or (None, None)
    conn.close()

    if not stored_password or not salt:
        return False

    hashed_password, _ = hash_password(password, salt)
    return hashed_password == stored_password