import os
import hashlib
import sqlite3

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(16)
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return (salt + hashed_password).hex(), salt

def register_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT UNIQUE, password_hash TEXT, salt BLOB)''')
    
    password_hash, salt = hash_password(password)
    
    try:
        c.execute("INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)", 
                  (username, password_hash, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print('Username already exists.')
    finally:
        conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT password_hash, salt FROM users WHERE username=?", (username,))
    row = c.fetchone()
    if not row:
        return False
    password_hash_db, salt_db = row
    
    password_hash_input, _ = hash_password(password, salt=salt_db)
    
    return password_hash_db == password_hash_input

# Example usage:
# register_user('john_doe', 'supersecret')
# print(verify_password('john_doe', 'supersecret'))