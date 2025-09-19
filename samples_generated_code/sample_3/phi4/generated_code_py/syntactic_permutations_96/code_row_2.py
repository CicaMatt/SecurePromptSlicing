import sqlite3
import hashlib
import os

# Create or connect to a SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create users table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    salt TEXT,
    hashed_password TEXT
)
''')

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)  # Generate a random 16-byte salt
    key = password.encode('utf-8') + salt
    return hashlib.pbkdf2_hmac('sha256', key, salt, 100000), salt

def register_user(username, password):
    hashed_password, salt = hash_password(password)
    
    try:
        cursor.execute('''
        INSERT INTO users (username, salt, hashed_password) 
        VALUES (?, ?, ?)
        ''', (username, salt.hex(), hashed_password.hex()))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")

def main():
    # Sample usage
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    register_user(username, password)

if __name__ == "__main__":
    main()