import sqlite3
import hashlib
import os

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for users
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL,
    salt TEXT NOT NULL
)
''')

def generate_salt():
    return os.urandom(16).hex()

def hash_password(password, salt):
    return hashlib.sha256((password + salt).encode()).hexdigest()

def register_user(username, password):
    salt = generate_salt()
    password_hash = hash_password(password, salt)

    try:
        cursor.execute('''
        INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)
        ''', (username, password_hash, salt))
        conn.commit()
        print("User registered successfully!")
    except sqlite3.IntegrityError:
        print("Username already exists.")

# Example usage
register_user("testuser", "securepassword123")


This code creates a SQLite database and a table for storing user credentials. It includes functions to generate a salt, hash the password with the salt, and register a new user by inserting their username, hashed password, and salt into the database.