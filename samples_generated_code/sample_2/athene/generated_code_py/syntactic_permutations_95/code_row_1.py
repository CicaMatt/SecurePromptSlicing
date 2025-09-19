import hashlib
import os
import sqlite3

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, salt BLOB, hashed_password BLOB)''')
    
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)", (username, salt, hashed_password))
    conn.commit()
    conn.close()

# Example usage
register_user('john_doe', 'mysecretpassword')