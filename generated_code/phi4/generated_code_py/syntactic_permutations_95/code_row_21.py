import sqlite3
from hashlib import pbkdf2_hmac
import os

# Create or connect to SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create users table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash BLOB NOT NULL,
    salt BLOB NOT NULL
)
''')

def hash_password(password, salt):
    return pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register(username, password):
    salt = os.urandom(16)
    password_hash = hash_password(password, salt)
    try:
        cursor.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)',
                       (username, password_hash, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")

def verify_password(stored_password_hash, stored_salt, provided_password):
    return hash_password(provided_password, stored_salt) == stored_password_hash

def login(username, password):
    cursor.execute('SELECT id, password_hash, salt FROM users WHERE username = ?', (username,))
    user = cursor.fetchone()
    
    if user and verify_password(user[1], user[2], password):
        print("Login successful.")
    else:
        print("Invalid username or password.")

# Example usage
register('testuser', 'securepassword123')
login('testuser', 'securepassword123')

conn.close()