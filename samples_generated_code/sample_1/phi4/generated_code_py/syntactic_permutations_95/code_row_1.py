import sqlite3
from hashlib import sha256
import os

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)
    salted_password = salt + password.encode('utf-8')
    return sha256(salted_password).hexdigest(), salt

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    hashed_password, salt = hash_password(password)
    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                       (username, hashed_password))
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print(f"Username {username} is already taken.")
    
    conn.commit()
    conn.close()

def main():
    create_database()
    
    while True:
        username = input("Enter a username: ")
        password = input("Enter a password: ")

        register_user(username, password)

        cont = input("Do you want to register another user? (yes/no): ").strip().lower()
        if cont != 'yes':
            break

if __name__ == "__main__":
    main()