import sqlite3
from hashlib import pbkdf2_hmac
import os

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            username TEXT PRIMARY KEY,
            password_hash BLOB,
            salt BLOB
        )
    ''')
    conn.commit()
    conn.close()

def generate_salt(length=16):
    return os.urandom(length)

def hash_password(password, salt):
    return pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    salt = generate_salt()
    password_hash = hash_password(password, salt)
    
    try:
        cursor.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)',
                       (username, password_hash, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def main():
    create_database()
    
    username = input("Enter a username: ")
    password = input("Enter a password: ")

    register_user(username, password)
    print(f"User '{username}' registered successfully.")

if __name__ == "__main__":
    main()