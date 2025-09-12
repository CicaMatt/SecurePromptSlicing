import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        hashed_password TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000), salt

def insert_user(username, password):
    hashed_password, salt = hash_password(password)
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    try:
        cursor.execute('''INSERT INTO users (username, hashed_password) 
                          VALUES (?, ?)''', (username, hashed_password.hex()))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def main():
    create_database()
    
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    insert_user(username, password)
    print("User registered successfully.")

if __name__ == "__main__":
    main()