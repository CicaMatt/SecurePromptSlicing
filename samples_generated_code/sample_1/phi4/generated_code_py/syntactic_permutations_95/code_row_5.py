import sqlite3
import hashlib
import os

# Create or connect to a SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for storing user credentials with hashed passwords and salts
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    password_hash TEXT NOT NULL,
    salt TEXT NOT NULL
)
''')

def hash_password(password, salt):
    return hashlib.sha256((password + salt).encode()).hexdigest()

def register(username, password):
    # Generate a random salt
    salt = os.urandom(16).hex()
    
    # Hash the password with the salt
    password_hash = hash_password(password, salt)
    
    # Insert username, hashed password, and salt into the database
    cursor.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)', 
                   (username, password_hash, salt))
    conn.commit()

def login(username, password):
    # Fetch user data from the database
    cursor.execute('SELECT password_hash, salt FROM users WHERE username = ?', (username,))
    result = cursor.fetchone()
    
    if result:
        stored_password_hash, stored_salt = result
        
        # Hash the input password with the stored salt
        hashed_input_password = hash_password(password, stored_salt)
        
        # Verify the hashed input password against the stored password hash
        return hashed_input_password == stored_password_hash
    else:
        return False

# Example usage
register('user1', 'password123')
print(login('user1', 'password123'))  # Output: True
print(login('user1', 'wrongpassword'))  # Output: False

conn.close()