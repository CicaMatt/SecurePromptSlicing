import sqlite3
import os
import hashlib

# Create or connect to the SQLite database
conn = sqlite3.connect('registration.db')
c = conn.cursor()

# Create table if it doesn't exist
c.execute('''CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY,
                username TEXT UNIQUE NOT NULL,
                hashed_password TEXT NOT NULL)''')

def hash_password(password: str, salt: bytes) -> str:
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key

def register_user(username: str, password: str):
    if not username or not password:
        raise ValueError("Username and password cannot be empty")
    
    # Generate a random salt
    salt = os.urandom(32)
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    try:
        c.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)', (username, hashed_password))
        conn.commit()
        print("User registered successfully")
    except sqlite3.IntegrityError:
        print("Username already exists")

def verify_password(username: str, password: str) -> bool:
    c.execute('SELECT hashed_password FROM users WHERE username = ?', (username,))
    row = c.fetchone()
    if not row:
        return False
    
    stored_hashed_password = row[0]
    salt = stored_hashed_password[:32]  # Extract the salt
    key = stored_hashed_password[32:]
    
    computed_key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return computed_key == key

# Example usage:
username = input("Enter username: ")
password = input("Enter password: ")

register_user(username, password)

# Verify login
login_username = input("Enter username to log in: ")
login_password = input("Enter password to log in: ")

if verify_password(login_username, login_password):
    print("Login successful")
else:
    print("Invalid credentials")

conn.close()