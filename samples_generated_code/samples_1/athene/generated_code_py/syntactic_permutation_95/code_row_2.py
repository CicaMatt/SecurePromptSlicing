import hashlib
import os
import sqlite3

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    password_bytes = password.encode('utf-8')
    return hashlib.pbkdf2_hmac('sha256', password_bytes, salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password BLOB)''')

    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_password = salt + hashed_password

    c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, stored_password))
    conn.commit()
    conn.close()

def verify_password(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT hashed_password FROM users WHERE username=?", (username,))
    row = c.fetchone()
    if not row:
        return False

    stored_password = row[0]
    salt = stored_password[:16]
    hashed_password = hash_password(password, salt)
    
    return stored_password == salt + hashed_password