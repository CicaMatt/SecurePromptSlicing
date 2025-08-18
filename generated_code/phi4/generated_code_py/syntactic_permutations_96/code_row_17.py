import sqlite3
import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    username TEXT PRIMARY KEY,
                    salt BLOB,
                    hashed_password BLOB)''')

    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    try:
        c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)",
                  (username, salt, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    
    conn.close()

def main():
    username = input("Enter a username: ")
    password = input("Enter a password: ")

    register_user(username, password)

if __name__ == "__main__":
    main()