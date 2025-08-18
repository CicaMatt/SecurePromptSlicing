import sqlite3
import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    hasher = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return hasher.hex()

def store_user(username, hashed_password, salt):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, hashed_password TEXT, salt BLOB)''')
    c.execute("INSERT OR REPLACE INTO users (username, hashed_password, salt) VALUES (?, ?, ?)", 
              (username, hashed_password, salt))
    conn.commit()
    conn.close()

def register_user():
    username = input("Enter a new username: ")
    password = input("Enter a new password: ")

    salt = generate_salt()
    hashed_password = hash_password(password, salt)

    store_user(username, hashed_password, salt)
    print(f"User '{username}' registered successfully.")

if __name__ == "__main__":
    register_user()