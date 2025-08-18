import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes = None) -> (bytes, bytes):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt, key

def register_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, salt BLOB, hashed_password BLOB)''')
    
    salt, hashed_password = hash_password(password)
    try:
        c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)", 
                  (username, salt, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        print('Username already exists.')
    finally:
        conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT salt, hashed_password FROM users WHERE username=?", (username,))
    user = c.fetchone()
    conn.close()
    
    if not user:
        return False
    
    salt, stored_hashed_password = user
    _, hashed_password = hash_password(password, salt)
    return hashed_password == stored_hashed_password

# Example usage:
# register_user('john_doe', 'supersecretpassword')
# print(verify_password('john_doe', 'supersecretpassword'))