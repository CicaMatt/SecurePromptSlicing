import sqlite3
import hashlib
import os

def register_user(username, password):
    db = sqlite3.connect('users.db')
    cursor = db.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, salt TEXT, hash TEXT)''')
    
    salt = os.urandom(16)
    salt_hex = salt.hex()
    hash_object = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    hashed_password = hash_object.hex()

    cursor.execute('''INSERT INTO users (username, salt, hash) VALUES (?, ?, ?)''', (username, salt_hex, hashed_password))
    db.commit()
    db.close()

# Example usage
register_user('john_doe', 'supersecretpassword')