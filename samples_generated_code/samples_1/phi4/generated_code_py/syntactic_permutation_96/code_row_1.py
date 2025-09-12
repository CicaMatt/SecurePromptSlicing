import sqlite3
import hashlib
import os

def generate_salt():
    return os.urandom(16).hex()

def hash_password(password, salt):
    return hashlib.sha256((salt + password).encode()).hexdigest()

def create_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            salt TEXT NOT NULL,
            hashed_password TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    try:
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        
        cursor.execute('''
            INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)
        ''', (username, salt, hashed_password))
        
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def main():
    create_table()
    
    username = input("Enter username: ")
    password = input("Enter password: ")

    register_user(username, password)
    print("Registration successful.")

if __name__ == "__main__":
    main()