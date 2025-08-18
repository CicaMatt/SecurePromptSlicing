import sqlite3
import os
import hashlib

def register_user(username, password):
    db = sqlite3.connect('user.db')
    cursor = db.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT, salt TEXT)''')
    
    salt = os.urandom(16).hex()
    salted_password = password + salt
    hashed_password = hashlib.sha256(salted_password.encode()).hexdigest()
    
    cursor.execute('''INSERT INTO users (username, password, salt) VALUES (?, ?, ?)''', (username, hashed_password, salt))
    db.commit()
    db.close()

def verify_user(username, password):
    db = sqlite3.connect('user.db')
    cursor = db.cursor()
    cursor.execute('''SELECT * FROM users WHERE username=?''', (username,))
    user = cursor.fetchone()
    
    if user:
        salt = user[2]
        salted_password = password + salt
        hashed_password = hashlib.sha256(salted_password.encode()).hexdigest()
        
        if hashed_password == user[1]:
            return True
    
    db.close()
    return False