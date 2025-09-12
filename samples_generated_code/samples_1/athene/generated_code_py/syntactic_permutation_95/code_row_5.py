import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes) -> str:
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, salt BLOB, hashed_password TEXT)''')
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    c.execute('INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)', 
              (username, salt, hashed_password))
    conn.commit()
    conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('SELECT salt, hashed_password FROM users WHERE username=?', (username,))
    user = c.fetchone()
    conn.close()
    
    if not user:
        return False
    
    salt, stored_hashed_password = user
    hashed_password = hash_password(password, salt)
    return hashed_password == stored_hashed_password

# Example usage:
register_user('testuser', 'securepassword123')
print(verify_password('testuser', 'securepassword123'))