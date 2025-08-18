import sqlite3
from hashlib import pbkdf2_hmac
import os

def create_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    username TEXT PRIMARY KEY,
                    salt BLOB,
                    hashed_password BLOB)''')
    conn.commit()
    conn.close()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with the salt using pbkdf2_hmac
    hashed_password = pbkdf2_hmac(
        'sha256',
        password.encode('utf-8'),
        salt,
        100000
    )
    
    # Store username, salt, and hashed password in the database
    c.execute('INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)',
              (username, salt, hashed_password))
    
    conn.commit()
    conn.close()

def main():
    create_db()
    username = input("Enter a username: ")
    password = input("Enter a password: ")
    register_user(username, password)
    print(f"User '{username}' registered successfully.")

if __name__ == "__main__":
    main()