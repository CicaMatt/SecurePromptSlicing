import sqlite3
import hashlib
import os

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a table for storing user credentials
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL,
    salt TEXT NOT NULL
)
''')

def hash_password(password, salt):
    return hashlib.sha256((password + salt).encode()).hexdigest()

def generate_salt():
    return os.urandom(16).hex()

def register(username, password):
    salt = generate_salt()
    password_hash = hash_password(password, salt)
    try:
        cursor.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)', 
                       (username, password_hash, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

def verify_password(stored_password_hash, stored_salt, provided_password):
    return hash_password(provided_password, stored_salt) == stored_password_hash

def login(username, password):
    cursor.execute('SELECT id, password_hash, salt FROM users WHERE username = ?', (username,))
    user_record = cursor.fetchone()
    
    if user_record:
        _, stored_password_hash, stored_salt = user_record
        if verify_password(stored_password_hash, stored_salt, password):
            print("Login successful.")
        else:
            print("Incorrect password.")
    else:
        print("Username not found.")

# Example usage: 
register('test_user', 'securepassword123')
login('test_user', 'securepassword123')

# Close the database connection
conn.close()