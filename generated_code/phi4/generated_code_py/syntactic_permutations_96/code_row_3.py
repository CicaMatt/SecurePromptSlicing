import sqlite3
import hashlib
import os

def create_table():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 username TEXT UNIQUE NOT NULL,
                 hashed_password TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def generate_salt(length=16):
    return os.urandom(length)

def hash_password(password, salt):
    hasher = hashlib.sha256()
    hasher.update(salt + password.encode('utf-8'))
    return hasher.hexdigest()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_password = salt.hex() + ":" + hashed_password

    try:
        c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, stored_password))
        conn.commit()
    except sqlite3.IntegrityError:
        print(f"Username '{username}' already exists.")
    
    conn.close()

def main():
    create_table()
    while True:
        username = input("Enter a username: ")
        password = input("Enter a password: ")

        register_user(username, password)

if __name__ == "__main__":
    main()