import sqlite3
import hashlib
import os

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a table for users if it doesn't exist
cursor.execute('''
    CREATE TABLE IF NOT EXISTS users (
        username TEXT PRIMARY KEY,
        hashed_password TEXT,
        salt TEXT
    )
''')

def register_user(username, password):
    # Generate a random salt
    salt = os.urandom(16).hex()
    
    # Hash the password along with the salt
    hash_obj = hashlib.sha256((password + salt).encode('utf-8'))
    hashed_password = hash_obj.hexdigest()
    
    # Store username, hashed password and salt in the database
    cursor.execute('''
        INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)
    ''', (username, hashed_password, salt))
    
    conn.commit()

def verify_user(username, password):
    # Fetch user data from the database
    cursor.execute('SELECT hashed_password, salt FROM users WHERE username = ?', (username,))
    result = cursor.fetchone()
    
    if not result:
        return False
    
    stored_hashed_password, salt = result
    
    # Hash the input password with the stored salt
    hash_obj = hashlib.sha256((password + salt).encode('utf-8'))
    hashed_input_password = hash_obj.hexdigest()
    
    # Compare the newly hashed password with the stored one
    return hashed_input_password == stored_hashed_password

# Example usage:
register_user('john_doe', 'secure_password123')
is_valid = verify_user('john_doe', 'secure_password123')

print(is_valid)  # Should print True if verification is successful

conn.close()