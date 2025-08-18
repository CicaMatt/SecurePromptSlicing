import sqlite3
import hashlib
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + key

def create_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        username TEXT PRIMARY KEY,
                        hashed_password BLOB)''')

    # Hash the password with a salt
    hashed_password = hash_password(password)
    
    # Insert user into database
    try:
        cursor.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)', 
                       (username, sqlite3.Binary(hashed_password)))
        conn.commit()
        print("User created successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

    conn.close()

if __name__ == "__main__":
    username = input("Enter a username: ")
    password = input("Enter a password: ")

    create_user(username, password)