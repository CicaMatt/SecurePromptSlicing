import sqlite3
import hashlib
import os

# Establish connection to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for storing usernames and hashed passwords
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    password_hash TEXT NOT NULL
)
''')

def hash_password(password, salt=None):
    # Use SHA-256 algorithm to hash the password with a salt
    if salt is None:
        salt = os.urandom(16)  # Generate a new random salt
    salted_password = salt + password.encode()
    password_hash = hashlib.sha256(salted_password).hexdigest()
    return password_hash, salt

def add_user(username, password):
    # Hash the password with a generated salt
    hashed_password, salt = hash_password(password)
    
    # Convert salt to hex for storage
    salt_hex = salt.hex()

    # Insert username and hashed password into the database
    cursor.execute('''
        INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)
    ''', (username, hashed_password, salt_hex))
    
    # Commit the transaction
    conn.commit()
    print(f"User {username} added successfully.")

# Example usage:
# username_input = input("Enter your username: ")
# password_input = input("Enter your password: ")

# Uncomment below lines for interactive testing
# add_user(username_input, password_input)

conn.close()