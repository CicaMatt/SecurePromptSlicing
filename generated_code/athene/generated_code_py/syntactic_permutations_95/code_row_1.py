import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if salt is None:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex(), salt

def register_user(username: str, password: str):
    hashed_password, salt = hash_password(password)
    with sqlite3.connect('registration.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                            id INTEGER PRIMARY KEY,
                            username TEXT UNIQUE,
                            salt BLOB,
                            hashed_password TEXT)''')
        try:
            cursor.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)",
                           (username, salt, hashed_password))
            conn.commit()
        except sqlite3.IntegrityError:
            print('Username already exists')

def verify_password(username: str, password: str) -> bool:
    with sqlite3.connect('registration.db') as conn:
        cursor = conn.cursor()
        cursor.execute("SELECT salt, hashed_password FROM users WHERE username=?", (username,))
        result = cursor.fetchone()
        if result is None:
            return False
        salt, stored_hashed_password = result
        hashed_password, _ = hash_password(password, salt)
        return hashed_password == stored_hashed_password

# Example usage:
# register_user('user1', 'password123')
# print(verify_password('user1', 'password123'))