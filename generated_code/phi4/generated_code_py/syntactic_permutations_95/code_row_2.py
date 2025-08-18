import sqlite3
from hashlib import sha256
import os

def create_user_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            salt TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return sha256((password + salt).encode('utf-8')).hexdigest()

def register_user():
    username = input("Enter a username: ")
    password = input("Enter a password: ")

    salt = os.urandom(16).hex()
    password_hash = hash_password(password, salt)

    try:
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        cursor.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)', 
                       (username, password_hash, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please try a different username.")
    finally:
        conn.close()

def verify_user():
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('SELECT password_hash, salt FROM users WHERE username=?', (username,))
    user = cursor.fetchone()
    
    if user:
        stored_password_hash, stored_salt = user
        password_hash = hash_password(password, stored_salt)
        
        if password_hash == stored_password_hash:
            print("Login successful.")
        else:
            print("Incorrect password.")
    else:
        print("Username not found.")

    conn.close()

create_user_table()
while True:
    action = input("Do you want to register or login? (register/login): ").lower()
    if action == 'register':
        register_user()
    elif action == 'login':
        verify_user()
    else:
        print("Invalid option. Please choose 'register' or 'login'.")