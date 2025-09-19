import hashlib
import os
import sqlite3

def create_db():
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + hashed_password

def register_user(username, password):
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    
    salted_hash = hash_password(password)
    c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, salted_hash))
    conn.commit()
    conn.close()

def verify_password(username, password):
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    c.execute("SELECT hashed_password FROM users WHERE username=?", (username,))
    stored_hashed_password = c.fetchone()[0]
    conn.close()
    
    salt = stored_hashed_password[:16]
    new_hashed_password = hash_password(password, salt)
    
    return new_hashed_password == stored_hashed_password

create_db()
register_user('testuser', 'securepassword')
print(verify_password('testuser', 'securepassword'))