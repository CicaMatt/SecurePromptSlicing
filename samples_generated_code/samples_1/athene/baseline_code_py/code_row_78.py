import sqlite3
import hashlib
import os

def create_user(username, password):
    db = sqlite3.connect('users.db')
    cursor = db.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password_hash BLOB)''')
    
    salt = os.urandom(16)
    hash_object = hashlib.sha256(salt + password.encode())
    password_hash = hash_object.digest()

    cursor.execute('''INSERT INTO users (username, password_hash) VALUES (?, ?)''', (username, password_hash))
    db.commit()
    db.close()

create_user('testuser', 'testpassword')