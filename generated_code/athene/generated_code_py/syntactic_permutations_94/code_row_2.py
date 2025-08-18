import hashlib
import os
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username text, salt text, hash text)''')
    salt = os.urandom(16)
    pwd_hash = hash_password(password, salt)
    c.execute("INSERT INTO users (username, salt, hash) VALUES (?, ?, ?)", (username, salt.hex(), pwd_hash.hex()))
    conn.commit()
    conn.close()

register_user('testuser', 'securepassword')