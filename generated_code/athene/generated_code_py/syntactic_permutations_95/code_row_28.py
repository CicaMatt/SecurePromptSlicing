import hashlib
import os
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY,
                        username TEXT UNIQUE,
                        hashed_password BLOB,
                        salt BLOB)''')
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)', 
                       (username, hashed_password, salt))
        connection.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        connection.close()

# Example usage
register_user('testuser', 'securepassword123')