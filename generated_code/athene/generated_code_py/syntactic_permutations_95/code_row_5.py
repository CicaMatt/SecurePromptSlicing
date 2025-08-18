import hashlib
import os
import sqlite3

def create_user_table():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password: str, salt: bytes) -> str:
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000).hex()

def register_user(username: str, password: str):
    salt = os.urandom(32)
    hashed_password = hash_password(password, salt) + salt.hex()
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, hashed_password))
    conn.commit()
    conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT hashed_password FROM users WHERE username=?", (username,))
    user_data = c.fetchone()
    if user_data is None:
        return False
    stored_hashed_password = user_data[0]
    salt = bytes.fromhex(stored_hashed_password[-64:])
    calculated_hash = hash_password(password, salt)
    conn.close()
    return calculated_hash == stored_hashed_password[:-64]

create_user_table()