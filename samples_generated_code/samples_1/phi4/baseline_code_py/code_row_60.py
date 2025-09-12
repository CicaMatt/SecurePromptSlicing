import sqlite3
from hashlib import sha256
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return sha256(salt + password.encode()).hexdigest()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        salt BLOB NOT NULL,
                        hashed_password TEXT NOT NULL)''')

    # Generate salt and hash password
    salt = generate_salt()
    hashed_password = hash_password(password, salt)

    # Insert into database
    try:
        cursor.execute('INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)',
                       (username, salt, hashed_password))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")
    
    # Close the connection
    conn.close()

# Example usage
register_user('testuser', 'password123')