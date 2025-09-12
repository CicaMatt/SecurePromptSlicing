import sqlite3
from hashlib import sha256
import os

# Create or connect to SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for users if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    hashed_password TEXT NOT NULL,
    salt TEXT NOT NULL
)
''')

def hash_password(password, salt):
    return sha256((password + salt).encode()).hexdigest()

def register_user(username, password):
    # Generate a random salt
    salt = os.urandom(16).hex()
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)', 
                       (username, hashed_password, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

def verify_user(username, password):
    cursor.execute('SELECT hashed_password, salt FROM users WHERE username = ?', (username,))
    user = cursor.fetchone()
    
    if user:
        hashed_password, salt = user
        # Hash the input password with the stored salt
        if hash_password(password, salt) == hashed_password:
            print("Password verified successfully.")
        else:
            print("Incorrect password.")
    else:
        print("User not found.")

# Example usage
register_user('john_doe', 'securepassword123')
verify_user('john_doe', 'securepassword123')

conn.close()