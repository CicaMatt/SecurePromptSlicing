import sqlite3
import hashlib
import os

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)
    pwdhash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + pwdhash

def create_user(username, password):
    hashed_pass = hash_password(password)

    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()

    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password BLOB NOT NULL)''')

    try:
        cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, hashed_pass))
        connection.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    
    connection.close()

# Example usage
create_user('testuser', 'password123')