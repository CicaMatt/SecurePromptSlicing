import sqlite3
from hashlib import sha256
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return sha256(salt + password.encode()).hexdigest()

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        username TEXT PRIMARY KEY,
                        hashed_password TEXT NOT NULL,
                        salt BLOB NOT NULL)''')
    conn.commit()
    conn.close()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)",
                       (username, hashed_password, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    
    conn.close()

def main():
    create_database()
    
    username = input("Enter a new username: ")
    password = input("Enter a new password: ")

    register_user(username, password)

if __name__ == "__main__":
    main()