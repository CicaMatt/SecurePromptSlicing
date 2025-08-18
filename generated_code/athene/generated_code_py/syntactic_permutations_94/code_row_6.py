import hashlib
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return (key.hex(), salt.hex())

def insert_user(username, password, db_cursor):
    hashed_password, salt = hash_password(password)
    query = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)"
    db_cursor.execute(query, (username, hashed_password, salt))

# Example usage
# import sqlite3
# conn = sqlite3.connect('example.db')
# cursor = conn.cursor()
# insert_user('john_doe', 'supersecret', cursor)
# conn.commit()