import sqlite3
import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def store_user(username, hashed_password_with_salt):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, hashed_password BLOB)''')
    c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, hashed_password_with_salt))
    conn.commit()
    conn.close()

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    hashed_password_with_salt = salt + hashed_password
    store_user(username, hashed_password_with_salt)

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    register_user(username, password)