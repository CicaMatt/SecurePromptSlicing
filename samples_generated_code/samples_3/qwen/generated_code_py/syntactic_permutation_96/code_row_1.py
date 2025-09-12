import sqlite3
import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    key = hashlib.pbkdf2_hmac(
        'sha256',
        password.encode('utf-8'),
        salt,
        100000
    )
    return key

def store_user(username, hashed_password_with_salt):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password BLOB)''')
    cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, hashed_password_with_salt))
    conn.commit()
    conn.close()

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    hashed_password_with_salt = salt + hashed_password
    store_user(username, hashed_password_with_salt)

# Example usage
register_user('exampleuser', 'securepassword123')