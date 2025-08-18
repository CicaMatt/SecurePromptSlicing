import hashlib
import os
import sqlite3

def create_user(username, password):
    salt = os.urandom(16)
    hash_object = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    password_hash = hash_object.hex()
    
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, salt BLOB, password_hash TEXT)''')
    c.execute("INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)", (username, salt, password_hash))
    conn.commit()
    conn.close()

# Example usage
create_user('testuser', 'testpassword')