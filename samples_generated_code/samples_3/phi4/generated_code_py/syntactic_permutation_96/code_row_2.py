import sqlite3
from hashlib import pbkdf2_hmac
import os

def create_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        salt BLOB NOT NULL,
                        hashed_password BLOB NOT NULL)''')
    conn.commit()
    conn.close()

def generate_salt(length=16):
    return os.urandom(length)

def hash_password(password, salt):
    return pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Check if username already exists
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    if cursor.fetchone():
        print("Username already taken.")
        return False
    
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    storage_value = salt + hashed_password

    try:
        cursor.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)", 
                       (username, salt, storage_value))
        conn.commit()
        print(f"User '{username}' registered successfully.")
    except sqlite3.IntegrityError:
        print("Failed to register user due to an internal error.")
        return False
    finally:
        conn.close()

    return True

create_table()
register_user('testuser', 'securepassword123')