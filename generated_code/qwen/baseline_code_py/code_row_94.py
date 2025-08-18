import sqlite3
from hashlib import pbkdf2_hmac
import os

def hash_password(password, salt):
    return pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def insert_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')

    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)

    try:
        c.execute("INSERT INTO users VALUES (?, ?, ?)", (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    insert_user(username, password)