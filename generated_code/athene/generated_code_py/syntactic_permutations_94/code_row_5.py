import hashlib
import os
import sqlite3

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password BLOB)''')
    
    salted_hash = hash_password(password)
    
    c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, salted_hash))
    conn.commit()
    conn.close()

register_user('exampleUser', 'examplePassword')