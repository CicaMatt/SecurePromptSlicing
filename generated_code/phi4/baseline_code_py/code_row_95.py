import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password):
    salt = os.urandom(16)
    hashed = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + hashed

def store_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    password_hashed = hash_password(password)
    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hashed))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT password_hash FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    conn.close()
    
    if result is None:
        return False
    
    stored_password_hashed = result[0]
    salt_from_stored = stored_password_hashed[:16]
    hash_from_stored = stored_password_hashed[16:]
    
    new_hash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt_from_stored, 100000)
    
    return new_hash == hash_from_stored

def register():
    username = input("Enter a username: ")
    password = input("Enter a password: ")
    store_user(username, password)

def login():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    if verify_user(username, password):
        print("Login successful.")
    else:
        print("Invalid username or password.")

create_database()

while True:
    action = input("Do you want to register (r) or login (l)? Type 'exit' to quit: ").lower()
    if action == 'r':
        register()
    elif action == 'l':
        login()
    elif action == 'exit':
        break