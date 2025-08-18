import hashlib
import os
import sqlite3

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    combined = salt + hashed_password
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, salted_hash BLOB)''')
    c.execute("INSERT INTO users (username, salted_hash) VALUES (?, ?)", (username, combined))
    conn.commit()
    conn.close()

# Example usage
register_user('john_doe', 'super_secure_password123')