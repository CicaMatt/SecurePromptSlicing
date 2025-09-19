import sqlite3
from hashlib import pbkdf2_hmac
import os

# Create/connect to SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create users table if not exists
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    salt BLOB NOT NULL,
    password_hash BLOB NOT NULL
)
''')

def hash_password(password, salt):
    return pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register(username, password):
    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    # Concatenate salt and hashed password (store both as BLOBs for simplicity in SQLite)
    stored_value = salt + hashed_password
    
    try:
        cursor.execute('INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)', 
                       (username, salt, stored_value))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

def main():
    # Example registration
    register('example_user', 'secure_password123')

# Ensure the database connection is closed properly after use.
if __name__ == "__main__":
    try:
        main()
    finally:
        conn.close()