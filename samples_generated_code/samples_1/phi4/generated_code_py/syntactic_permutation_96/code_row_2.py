import sqlite3
import hashlib
import os

# Establish connection to SQLite database (or create if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for users if it doesn't already exist
cursor.execute('''
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT UNIQUE NOT NULL,
        salt BLOB NOT NULL,
        hashed_password BLOB NOT NULL
    )
''')

def hash_password(password: str, salt: bytes) -> bytes:
    """Hash a password with the given salt using SHA-256."""
    return hashlib.sha256(salt + password.encode()).digest()

def register_user(username: str, password: str):
    """Register a user by hashing their password and storing it in the database."""
    # Generate a random 16-byte salt
    salt = os.urandom(16)
    
    # Hash the password with the generated salt
    hashed_password = hash_password(password, salt)

    try:
        # Insert new user into the database
        cursor.execute('''
            INSERT INTO users (username, salt, hashed_password) 
            VALUES (?, ?, ?)
        ''', (username, salt, hashed_password))
        
        conn.commit()
        print("User registered successfully.")
    
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")

def main():
    # Example usage
    username = input("Enter username: ")
    password = input("Enter password: ")

    register_user(username, password)

if __name__ == "__main__":
    try:
        main()
    finally:
        conn.close()