import sqlite3
import hashlib
import os

# Create or connect to a SQLite database
conn = sqlite3.connect('registration.db')
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL
)
''')

def generate_salt(length=16):
    """Generate a random salt."""
    return os.urandom(length)

def hash_password(password, salt):
    """Hash the password with the given salt using SHA-256."""
    hasher = hashlib.sha256()
    hasher.update(salt + password.encode('utf-8'))
    return hasher.hexdigest()

def register_user(username, password):
    """Register a user by storing the username and hashed password with salt in the database."""
    salt = generate_salt()
    password_hash = hash_password(password, salt)
    
    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', 
                       (username, password_hash + salt.hex()))
        conn.commit()
        print(f"User '{username}' registered successfully.")
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}. Username may already be taken.")

# Example usage
register_user('testuser', 'securepassword123')

# Close the connection to the database
conn.close()