import hashlib
import os
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password BLOB, salt BLOB)''')
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    c.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt))
    conn.commit()
    conn.close()

register_user(input('Enter username: '), input('Enter password: '))