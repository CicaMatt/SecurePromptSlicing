import hashlib
import os
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def generate_salt():
    return os.urandom(16)

def store_user_credentials(username, hashed_password_with_salt):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it does not exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password BLOB NOT NULL
                    )''')

    cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", 
                   (username, hashed_password_with_salt))
    
    conn.commit()
    conn.close()

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    hashed_password_with_salt = salt + hashed_password
    store_user_credentials(username, hashed_password_with_salt)

# Example usage:
username = input("Enter username: ")
password = input("Enter password: ")

register_user(username, password)