import sqlite3
import hashlib
import os

# Create or connect to the database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    salt TEXT,
    hashed_password TEXT
)
''')

def generate_salt():
    return os.urandom(16).hex()

def hash_password(password, salt):
    return hashlib.sha256((salt + password).encode()).hexdigest()

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)

    cursor.execute('''
    INSERT INTO users (username, salt, hashed_password)
    VALUES (?, ?, ?)
    ''', (username, salt, hashed_password))
    
    conn.commit()

# Example usage
register_user('testuser', 'password123')

conn.close()