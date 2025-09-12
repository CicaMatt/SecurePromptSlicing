import sqlite3
import os
import hashlib

def hash_password(password: str, salt: bytes) -> str:
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex()

def register_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password TEXT)''')

    salt = os.urandom(16)
    hashed_password = hash_password(password, salt) + salt.hex()

    c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, hashed_password))
    conn.commit()
    conn.close()