import sqlite3
import os
from hashlib import sha256

def register_user(username, password):
    db = sqlite3.connect('users.db')
    cursor = db.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT, salt TEXT)''')
    
    salt = os.urandom(16)
    hashed_password = sha256(password.encode() + salt).hexdigest()
    
    cursor.execute('''INSERT INTO users(username, password, salt) VALUES (?, ?, ?)''', (username, hashed_password, salt.hex()))
    db.commit()
    db.close()

def verify_user(username, password):
    db = sqlite3.connect('users.db')
    cursor = db.cursor()
    cursor.execute('''SELECT * FROM users WHERE username=?''', (username,))
    user = cursor.fetchone()
    
    if not user:
        return False
    
    salt = bytes.fromhex(user[2])
    hashed_password = sha256(password.encode() + salt).hexdigest()
    
    valid = hashed_password == user[1]
    db.close()
    return valid