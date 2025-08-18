import hashlib
import os
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def store_user(username, password):
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    stored_password = salt + hashed_password

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, password BLOB)''')
    c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, stored_password))
    conn.commit()
    conn.close()

if __name__ == "__main__":
    username = input("Enter username: ")
    password = input("Enter password: ")
    store_user(username, password)