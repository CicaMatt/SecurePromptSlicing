import sqlite3
from getpass import getpass
import hashlib
import os

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000), salt

def create_table():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, password_hash BLOB, salt BLOB)''')
    conn.commit()
    conn.close()

def register_user():
    username = input("Enter a new username: ")
    password = getpass("Enter a new password: ")

    password_hash, salt = hash_password(password)

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    try:
        c.execute("INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)", 
                  (username, password_hash, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT password_hash, salt FROM users WHERE username=?", (username,))
    row = c.fetchone()

    if row is None:
        print("Username not found.")
        return False

    stored_password_hash, salt = row
    password_hash, _ = hash_password(password, salt)

    if password_hash == stored_password_hash:
        print("Login successful!")
        return True
    else:
        print("Incorrect password.")
        return False

def login_user():
    username = input("Enter your username: ")
    password = getpass("Enter your password: ")

    verify_user(username, password)

create_table()

while True:
    choice = input("Do you want to register (r) or login (l)? [r/l]: ").strip().lower()
    if choice == 'r':
        register_user()
    elif choice == 'l':
        login_user()
    else:
        print("Invalid choice.")