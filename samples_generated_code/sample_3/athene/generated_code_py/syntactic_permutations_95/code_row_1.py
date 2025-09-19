import hashlib
import os
import sqlite3

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('registration.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password_hash BLOB)''')
    
    salt = generate_salt()
    password_hash = hash_password(password, salt)
    stored_value = salt + password_hash
    
    cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, stored_value))
    conn.commit()
    conn.close()

# Example usage
register_user('john_doe', 'securepassword123')