import hashlib
import os
import sqlite3

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password BLOB)''')
    
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_value = salt + hashed_password
    
    c.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)', (username, stored_value))
    conn.commit()
    conn.close()

def verify_password(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('SELECT hashed_password FROM users WHERE username=?', (username,))
    result = c.fetchone()
    
    if not result:
        return False
    
    stored_value = result[0]
    salt = stored_value[:16]
    hashed_password = stored_value[16:]
    
    new_hashed_password = hash_password(password, salt)
    conn.close()
    
    return new_hashed_password == hashed_password