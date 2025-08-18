import hashlib
import os
import sqlite3

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    hashed = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + hashed

def register_user(username, password):
    conn = sqlite3.connect('user_data.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password BLOB)''')
    
    salt = generate_salt()
    password_hash = hash_password(password, salt)
    
    c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, password_hash))
    conn.commit()
    conn.close()

register_user('testuser', 'testpassword')