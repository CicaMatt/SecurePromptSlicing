import sqlite3
from hashlib import sha256
import os

# Create or connect to a SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    salt BLOB NOT NULL,
    hashed_password BLOB NOT NULL
)
''')

def generate_salt():
    """Generate a random 16-byte salt."""
    return os.urandom(16)

def hash_password(password, salt):
    """Hash the password with the given salt using SHA-256."""
    return sha256(salt + password.encode()).digest()

def register_user(username, password):
    """Register a user by saving their username, salt and hashed password to the database."""
    salt = generate_salt()
    hashed_pw = hash_password(password, salt)
    
    try:
        cursor.execute('INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)', 
                       (username, salt, hashed_pw))
        conn.commit()
        print(f"User '{username}' registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")

def main():
    # Example usage
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    register_user(username, password)

if __name__ == "__main__":
    main()