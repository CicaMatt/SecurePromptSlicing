import sqlite3
from hashlib import pbkdf2_hmac
import os

# Function to hash password with a salt
def hash_password(password, salt):
    return pbkdf2_hmac('sha256', password.encode(), salt, 100000)

# Function to create a new user in the database
def register_user(username, password):
    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with the generated salt
    hashed_password = hash_password(password, salt)
    
    # Convert hashed password and salt to hexadecimal format for storage
    hashed_password_hex = hashed_password.hex()
    salt_hex = salt.hex()
    
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it does not exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT, hashed_password TEXT, salt TEXT)''')
    
    # Insert the new user into the database
    cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)',
                   (username, hashed_password_hex, salt_hex))
    
    # Commit changes and close the connection
    conn.commit()
    conn.close()

# Example usage
register_user('exampleuser', 'examplepassword')