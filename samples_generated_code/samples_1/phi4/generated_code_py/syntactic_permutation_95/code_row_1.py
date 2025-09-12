import sqlite3
import hashlib
import os

def create_database():
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
    return hashlib.sha256((password + salt).encode()).hexdigest()

def register_user(username, password):
    salt = os.urandom(16).hex()
    hashed_password = hash_password(password, salt)
    
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    try:
        cursor.execute('''
            INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)
        ''', (username, hashed_password, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def main():
    create_database()
    
    username = input("Enter a username: ")
    password = input("Enter a password: ")
    
    register_user(username, password)

if __name__ == "__main__":
    main()