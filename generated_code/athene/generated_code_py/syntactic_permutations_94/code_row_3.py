import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes) -> str:
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register_user(username: str, password: str):
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, salt BLOB, hashed_password TEXT)''')
    c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)", (username, salt, hashed_password))
    conn.commit()
    conn.close()

register_user(input('Enter username: '), input('Enter password: '))