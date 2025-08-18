import sqlite3
import hashlib
import os

# Create a connection to the SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('user_database.db')
cursor = conn.cursor()

# Create a table for storing user credentials
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    salt TEXT NOT NULL,
    hashed_password TEXT NOT NULL
)
''')

def hash_password(password, salt):
    """Hashes the password with the given salt using SHA-256."""
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register_user(username, password):
    """Registers a new user by hashing their password and storing it in the database."""
    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    try:
        # Store the username, salt, and hashed password in the database
        cursor.execute('INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)', 
                       (username, salt.hex(), hashed_password))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")

# Example usage
register_user('exampleuser', 'securepassword123')

# Close the database connection
conn.close()