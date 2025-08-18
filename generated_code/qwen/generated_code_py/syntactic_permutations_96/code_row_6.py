import hashlib
import os
import sqlite3

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def store_credentials(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    conn = sqlite3.connect('credentials.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, salt BLOB, hashed_password BLOB)''')
    cursor.execute('INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)', (username, salt, hashed_password))
    conn.commit()
    conn.close()

if __name__ == "__main__":
    username = input("Enter username: ")
    password = input("Enter password: ")
    store_credentials(username, password)