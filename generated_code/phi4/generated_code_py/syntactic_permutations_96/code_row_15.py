import hashlib
import os
import sqlite3

# Create or connect to a SQLite database
conn = sqlite3.connect('user_data.db')
cursor = conn.cursor()

# Create users table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    salt TEXT NOT NULL,
    hashed_password TEXT NOT NULL
)
''')

def generate_salt():
    """Generate a 16-byte salt."""
    return os.urandom(16).hex()

def hash_password(password, salt):
    """Hash the password using SHA256 with a salt."""
    salted_pass = (salt + password).encode('utf-8')
    return hashlib.sha256(salted_pass).hexdigest()

def register_user(username, password):
    """Register a new user with a username and password."""
    try:
        # Generate a salt
        salt = generate_salt()
        
        # Hash the password with the generated salt
        hashed_password = hash_password(password, salt)
        
        # Insert into database
        cursor.execute('''
        INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)
        ''', (username, salt, hashed_password))
        
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

# Example usage:
register_user('exampleuser', 'password123')

# Close the database connection
conn.close()