import sqlite3
from hashlib import pbkdf2_hmac
import os

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            salt BLOB NOT NULL,
            hashed_password BLOB NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute(
            'INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)',
            (username, salt, hashed_password)
        )
        conn.commit()
        print("User registered successfully!")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    
    conn.close()

def main():
    create_database()
    username = input("Enter a new username: ")
    password = input("Enter a new password: ")
    register_user(username, password)

if __name__ == "__main__":
    main()