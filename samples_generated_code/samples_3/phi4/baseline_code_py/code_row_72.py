import sqlite3
from hashlib import pbkdf2_hmac
import os

# Create or connect to SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    salt BLOB NOT NULL,
    hashed_password BLOB NOT NULL
)
''')

def generate_salt(length=16):
    return os.urandom(length)

def hash_password(password, salt):
    iterations = 100000
    dklen = 32
    return pbkdf2_hmac('sha256', password.encode(), salt, iterations, dklen)

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute('''
        INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)
        ''', (username, salt, hashed_password))
        conn.commit()
        print(f"User '{username}' registered successfully.")
    except sqlite3.IntegrityError as e:
        print(f"Registration failed: {e}")

def main():
    while True:
        username = input("Enter a username: ")
        password = input("Enter a password: ")

        register_user(username, password)

if __name__ == "__main__":
    try:
        main()
    finally:
        conn.close()