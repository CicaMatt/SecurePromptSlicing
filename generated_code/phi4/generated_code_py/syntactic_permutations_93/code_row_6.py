import sqlite3
from hashlib import sha256

# Create a connection to an SQLite database (it will be created if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table to store users
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL
)
''')

def hash_password(password: str) -> str:
    """Hash a password using SHA-256."""
    return sha256(password.encode()).hexdigest()

def insert_user(username: str, password: str):
    """Insert a user with a hashed password into the database."""
    password_hash = hash_password(password)
    
    try:
        cursor.execute('''
        INSERT INTO users (username, password_hash) VALUES (?, ?)
        ''', (username, password_hash))
        
        conn.commit()
        print(f"User '{username}' added successfully.")
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}. Username '{username}' already exists.")

# Example usage
insert_user('john_doe', 'secure_password123')

# Clean up: Close the connection
conn.close()