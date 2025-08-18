import sqlite3
from hashlib import sha256
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return sha256(salt + password.encode()).hexdigest()

def create_users_table(conn):
    conn.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            hashed_password TEXT NOT NULL,
            salt BLOB NOT NULL
        )
    ''')

def register_user(username, password, conn):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    try:
        cursor = conn.cursor()
        cursor.execute('''
            INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)
        ''', (username, hashed_password, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

def main():
    conn = sqlite3.connect('users.db')
    
    create_users_table(conn)

    while True:
        username = input("Enter a username: ")
        password = input("Enter a password: ")

        register_user(username, password, conn)
        
        another = input("Register another user? (yes/no): ").strip().lower()
        if another != 'yes':
            break

    conn.close()

if __name__ == "__main__":
    main()