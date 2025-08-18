import hashlib
import os
import sqlite3

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return (salt, hashed_password)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, salt BLOB, hashed_password BLOB)''')
    
    salt, hashed_password = hash_password(password)
    
    c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)", 
              (username, salt, hashed_password))
    
    conn.commit()
    conn.close()

# Example usage:
register_user('john_doe', 'supersecurepassword123')