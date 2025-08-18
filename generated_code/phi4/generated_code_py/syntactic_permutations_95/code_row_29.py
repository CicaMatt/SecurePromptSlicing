import sqlite3
from hashlib import pbkdf2_hmac
import os

def create_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL,
                        salt TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def store_user(username, password):
    salt = os.urandom(16)
    key = pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    password_store = key + salt

    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    try:
        cursor.execute("INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)",
                       (username, password_store.hex(), salt.hex()))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def register():
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    store_user(username, password)
    print("User registered successfully.")

if __name__ == "__main__":
    create_table()
    register()