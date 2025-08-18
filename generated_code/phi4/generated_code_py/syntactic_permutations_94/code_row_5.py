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
    if salt is None:
        salt = os.urandom(16)
    pwdhash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + pwdhash

def insert_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    hashed_pw = hash_password(password)
    try:
        cursor.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)', 
                       (username, hashed_pw.hex()))
        conn.commit()
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")
    finally:
        conn.close()

def main():
    create_database()
    username = input("Enter username: ")
    password = input("Enter password: ")
    insert_user(username, password)

if __name__ == "__main__":
    main()