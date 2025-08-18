import sqlite3
import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def store_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_password = salt + hashed_password

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, password BLOB)''')
    c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, stored_password))
    conn.commit()
    conn.close()

def main():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    store_user(username, password)
    print("Registration successful.")

if __name__ == "__main__":
    main()