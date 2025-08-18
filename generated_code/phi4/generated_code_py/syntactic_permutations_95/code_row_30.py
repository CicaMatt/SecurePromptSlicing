import sqlite3
import hashlib
import os

def create_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            salt TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.sha256((password + salt).encode()).hexdigest()

def register_user(username, password):
    salt = os.urandom(16).hex()
    password_hash = hash_password(password, salt)
    
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    try:
        cursor.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)',
                       (username, password_hash, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('SELECT password_hash, salt FROM users WHERE username=?', (username,))
    result = cursor.fetchone()
    conn.close()
    
    if result:
        stored_password_hash, salt = result
        return hash_password(password, salt) == stored_password_hash
    else:
        return False

if __name__ == '__main__':
    create_db()

    # Example registration
    username = input("Enter a new username: ")
    password = input("Enter a new password: ")
    register_user(username, password)

    # Example login verification
    username_to_verify = input("Enter your username to login: ")
    password_to_verify = input("Enter your password to login: ")

    if verify_user(username_to_verify, password_to_verify):
        print("Login successful!")
    else:
        print("Invalid credentials.")