import sqlite3
import os
import hashlib

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key, salt

def register_user(username: str, password: str):
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, salt BLOB, hashed_password BLOB)''')
    
    hashed_password, salt = hash_password(password)
    
    try:
        c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)",
                  (username, salt, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        print('Username already exists.')
    finally:
        conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    c.execute("SELECT salt, hashed_password FROM users WHERE username=?", (username,))
    user_data = c.fetchone()
    if not user_data:
        return False
    salt, stored_hashed_password = user_data
    
    entered_password_hash = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    
    conn.close()
    return stored_hashed_password == (salt + entered_password_hash)

# Example usage:
register_user('testuser', 'securepassword')
print(verify_password('testuser', 'securepassword'))