import hashlib
import os
import sqlite3

def create_db():
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password: str, salt: bytes) -> str:
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key

def register_user(username: str, password: str):
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, hashed_password))
    conn.commit()
    conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    c.execute("SELECT hashed_password FROM users WHERE username=?", (username,))
    result = c.fetchone()
    if not result:
        return False
    
    stored_hashed_password = result[0]
    salt = stored_hashed_password[:16]
    key = stored_hashed_password[16:]
    
    new_key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    
    conn.close()
    return new_key == key

create_db()

# Example usage:
register_user('john_doe', 'securepassword')
print(verify_password('john_doe', 'securepassword'))  # Should print True