import hashlib
import os
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    salt = os.urandom(32)
    hashed_password = hash_password(password, salt)
    
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, salt BLOB, password BLOB)''')
    c.execute("INSERT INTO users (username, salt, password) VALUES (?, ?, ?)", (username, salt, hashed_password))
    
    conn.commit()
    conn.close()

# Example usage
register_user('john_doe', 'mySecurePassword123')